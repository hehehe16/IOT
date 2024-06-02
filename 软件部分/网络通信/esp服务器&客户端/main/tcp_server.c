/* BSD Socket API Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
#include "string.h"

#include "driver/uart.h"



#define PORT                        80
#define KEEPALIVE_IDLE              CONFIG_EXAMPLE_KEEPALIVE_IDLE
#define KEEPALIVE_INTERVAL          CONFIG_EXAMPLE_KEEPALIVE_INTERVAL
#define KEEPALIVE_COUNT             CONFIG_EXAMPLE_KEEPALIVE_COUNT

#define HOST_IP_ADDR "8.130.87.75"
static EventGroupHandle_t s_wifi_event_group;
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

QueueHandle_t uart_Queue;  //uart事件列表
uint8_t Data[128]={0};    //接收数据缓存

uint8_t uart_re_state = 0; //全局串口接收标志位
int client[5]={0};
int sock = 0;

static const char *TAG = "server";
static const char *uart = "uart";


void socket_send(int socket,const void *dataptr,size_t size)
{
    int to_writr = size;
    while(to_writr>0)
    {
        int writen = send(socket,dataptr + (size - to_writr),to_writr,0);
        if (writen < 0) {
            ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
            break;
        }
        to_writr -= writen; 
    }
}
void handle_client_task(void *pt){
    int len;
    char rx_buffer[128];//接收的数据
    int sock = (int)pt;//创建任务传过来的参数（sock句柄）
    int connecttag;//断开连接结束整个任务的标记
    while (1)
    {
        do {

            len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);//接收(有数据时>0)
            if (len < 0) {
                ESP_LOGE(TAG, "Error occurred during receiving: errno %d", errno);
            } else if (len == 0) {
                ESP_LOGW(TAG, "Connection closed");
                shutdown(sock, 0);
                close(sock);
                connecttag = 1;
            } else {
                rx_buffer[len] = 0; // Null-terminate whatever is received and treat it like a string将接收到的任何内容终止为空，并将其视为字符串
                ESP_LOGI(TAG, " Received %d bytes: %s", len, rx_buffer);

                // send() can return less bytes than supplied length. Send()返回的字节数可能少于提供的长度
                // Walk-around for robust implementation.
                int to_write = len;
                while (to_write > 0) {
                    int written = send(sock, rx_buffer + (len - to_write), to_write, 0);//？
                    if (written < 0) {
                        ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                    }
                    to_write -= written;//to_write = 0
                }
            }
        } while (len > 0); //有数据接收就继续循环

        vTaskDelay(1000/portTICK_PERIOD_MS);
        if (connecttag)
        {
            break;//跳出最外面的while
        }
    }
    vTaskDelete(NULL);//删除整个task，不然会触发看门狗
    
}
    

void tcp_server_config(void *pvParameters){
    char addr_str[128];
    int addr_family = (int)pvParameters;
    int ip_protocol = 0;
    int keepAlive = 1;
    int keepIdle = KEEPALIVE_IDLE;
    int keepInterval = KEEPALIVE_INTERVAL;
    int keepCount = KEEPALIVE_COUNT;
    struct sockaddr_storage dest_addr;
    //如果返回的是IPV4地址（AF_INET在taskcreate里就传参了 pvParameters ->(void *)AF_INET ）
    if (addr_family == AF_INET)
    {
        struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
        dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);//将一个32位数从主机字节顺序转换成网络字节顺序（返回值是一个32位的网络字节顺序）
        dest_addr_ip4->sin_family = AF_INET;
        dest_addr_ip4->sin_port = htons(PORT);//将一个16位数从主机字节顺序转换成网络字节顺序（返回值是一个16位的网络字节顺序）
        ip_protocol = IPPROTO_IP;
    }
#ifdef CONFIG_EXAMPLE_IPV6
    else if (addr_family == AF_INET6) {
        struct sockaddr_in6 *dest_addr_ip6 = (struct sockaddr_in6 *)&dest_addr;
        bzero(&dest_addr_ip6->sin6_addr.un, sizeof(dest_addr_ip6->sin6_addr.un));
        dest_addr_ip6->sin6_family = AF_INET6;
        dest_addr_ip6->sin6_port = htons(PORT);
        ip_protocol = IPPROTO_IPV6;
    }
#endif
    ESP_LOGI(TAG,"1.初始化socket..........");
    int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
    if (listen_sock < 0)
    {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        vTaskDelete(NULL);
        return;
    }
    int opt = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));//获取的嵌套字，选择所在的协议层，设置的选项（允许复用本地地址和端口），存放选项待设置的新值的缓冲区，缓冲区长度
#if defined(CONFIG_EXAMPLE_IPV4) && defined(CONFIG_EXAMPLE_IPV6)
    // Note that by default IPV6 binds to both protocols, it is must be disabled
    // if both protocols used at the same time (used in CI)
    setsockopt(listen_sock, IPPROTO_IPV6, IPV6_V6ONLY, &opt, sizeof(opt));
#endif
    ESP_LOGI(TAG, "Socket created");

    ESP_LOGI(TAG,"2.正在绑定端口..........");
    int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err != 0) {
        ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        ESP_LOGE(TAG, "IPPROTO: %d", addr_family);
        goto CLEAN_UP;
    }
    ESP_LOGI(TAG, "Socket bound, port %d", PORT);

    ESP_LOGI(TAG,"3.正在监听客户端..........");
    err = listen(listen_sock, 1);//同一时间最多可以收到1个客户端请求
    if (err != 0)
    {
        ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
        goto CLEAN_UP;
    }
    ESP_LOGI(TAG, "Socket listening");
    ESP_LOGI(TAG,"4.正在创建与客户端的连接通道..........");
        while (1) {
        struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
        socklen_t addr_len = sizeof(source_addr);
        int sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);//等待客户端连接，如果一直没有客户端连接将一直阻塞（成功：返回嵌套字 失败：return -1）
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
            break;
        }

        // Set tcp keepalive option 
        setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(int));//SOL_SOCKET通用套接字选项；SO_KEEPALIVE保持连接；keepalive非0值，开启keepalive属性
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &keepIdle, sizeof(int));//IPPROTO_TCP TCP选项；TCP_KEEPIDLE 设置允许没有数据传输时（空闲）的时间
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(int));//TCP_KEEPINTVL 当超过允许的空闲时间仍然没有数据传输时，每隔TCP_KEEPINTVL设定的时间发送一次探测包
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &keepCount, sizeof(int));//TCP_KEEPCNT 允许发送探测包最多次数
        
        // Convert ip address to string 将ip地址转换为字符串
        //判断存放地址sockaddr_storage结构体里的ss_family是否为ipv4的地址
        if (source_addr.ss_family == PF_INET) {
            //把地址sin_addr转成字符串存到缓冲区addr_str映射到lwip并返回地址
            inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addr_str, sizeof(addr_str) - 1);
        }
#ifdef CONFIG_EXAMPLE_IPV6
        else if (source_addr.ss_family == PF_INET6) {
            inet6_ntoa_r(((struct sockaddr_in6 *)&source_addr)->sin6_addr, addr_str, sizeof(addr_str) - 1);
        }
#endif
        ESP_LOGI(TAG, "Socket accepted ip address: %s", addr_str);


        xTaskCreate(handle_client_task, "handle_client_task", 4096, (void *)sock, 5, NULL);
        static int i = 0;
        
        client[i] = sock;
        i++;
        // do_retransmit(sock);

        // shutdown(sock, 0);
        // ESP_LOGE(TAG,"shutdown");
        // close(sock);
    }

    CLEAN_UP:
    close(listen_sock);
    vTaskDelete(NULL);
}
void usertcp_server(void){
    #ifdef CONFIG_EXAMPLE_IPV4
        xTaskCreate(tcp_server_config, "tcp_server", 4096, (void *)AF_INET, 5, NULL);
    #endif
    #ifdef CONFIG_EXAMPLE_IPV6
        xTaskCreate(tcp_server_config, "tcp_server", 4096, (void *)AF_INET6, 5, NULL);
    #endif
}

static void wifi_event(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base ==IP_EVENT &&event_id == IP_EVENT_AP_STAIPASSIGNED) 
    {
        ip_event_ap_staipassigned_t* event = (ip_event_ap_staipassigned_t*) event_data;
        ESP_LOGI(TAG,"设备接入:%d.%d.%d.%d",IP2STR(&event->ip));
    }

}
static void uart_event(void* arg)           //串口事件
{
    uart_event_t  event;
    int length = 0;
    while(1)
    {
    if(xQueueReceive(uart_Queue,(void *)&event,portMAX_DELAY))
    {
        switch(event.type)
        {
            case UART_DATA:
            {

                uart_re_state = 1;
                uart_get_buffered_data_len(UART_NUM_2,(size_t *)&length);
                length = uart_read_bytes(UART_NUM_2,Data,length,100);

                //uart_write_bytes(UART_NUM_2,Data,length);
                ESP_LOGI(uart,"接收:%s",(char *)(Data));
                
                // int to_tran_client = 0;              //服务器模式
                // if(Data[0] == 0x01)
                // {
                    
                //     to_tran_client = client[0];
                // }
                // else if(Data[0] == 0x02)
                // {
                //     to_tran_client = client[1];
                // }

                int tr_len = length;
                int to_write = tr_len;
                while (to_write > 0) {
                    int written = send(sock, (&(Data)) +(length - to_write), to_write, 0);
                    if (written < 0) {
                        ESP_LOGI(TAG, "TCP发送错误: errno %d", errno);
                        break;
                    }
                    to_write -= written;//to_write = 0
                }                
                break;
            }
            case UART_BUFFER_FULL:
            {
                ESP_LOGI(uart, "数据缓存区已满");
                break;
            }
            default:
            {
                break;
            }            
        }

    }
    }
    vTaskDelete(NULL);  
}

void tcp_client(void)
{
    char rx_buffer[128];
    char host_ip[] = HOST_IP_ADDR;
    int addr_family = 0;
    int ip_protocol = 0;

    while (1) {
#if defined(CONFIG_EXAMPLE_IPV4)
        struct sockaddr_in dest_addr;
        inet_pton(AF_INET, host_ip, &dest_addr.sin_addr);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(PORT);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;
#elif defined(CONFIG_EXAMPLE_SOCKET_IP_INPUT_STDIN)
        struct sockaddr_storage dest_addr = { 0 };
        ESP_ERROR_CHECK(get_addr_from_stdin(PORT, SOCK_STREAM, &ip_protocol, &addr_family, &dest_addr));
#endif

        sock =  socket(addr_family, SOCK_STREAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Socket created, connecting to %s:%d", host_ip, PORT);

        int err = connect(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if (err != 0) {
            ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Successfully connected");
        socket_send(sock, "esp32", strlen("esp32"));
        while (1) {

            int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
            // Error occurred during receiving
            if (len < 0) {
                ESP_LOGE(TAG, "recv failed: errno %d", errno);
                break;
            }
            
            // Data received
            else {
                rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
                ESP_LOGI(TAG, "Received %d bytes from %s:", len, host_ip);
                ESP_LOGI(TAG, "%s", rx_buffer);
            }
            uart_write_bytes(UART_NUM_2,rx_buffer,len);
        }

        if (sock != -1) {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
}


static void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    
    int s_retry_num = 0;
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) 
    {
        esp_wifi_connect();
    } 
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) 
    {
        if (s_retry_num < 5) 
        {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        } 
        else 
        {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } 
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) 
    {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());      
    ESP_ERROR_CHECK(esp_netif_init());     
    ESP_ERROR_CHECK(esp_event_loop_create_default());       
    //esp_event_handler_instance_register(IP_EVENT,IP_EVENT_AP_STAIPASSIGNED,&wifi_event,NULL,NULL); 
    esp_event_handler_instance_register(WIFI_EVENT,ESP_EVENT_ANY_ID,&event_handler,NULL,NULL);
    esp_event_handler_instance_register(IP_EVENT,IP_EVENT_STA_GOT_IP,&event_handler,NULL,NULL);

    uart_config_t uart_cfg={
        .baud_rate=115200,
        .data_bits = UART_DATA_8_BITS,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .parity = UART_PARITY_DISABLE,
        .rx_flow_ctrl_thresh =122,
        .stop_bits = UART_STOP_BITS_1
    };
    uart_param_config(UART_NUM_2, &uart_cfg);
    uart_set_pin(UART_NUM_2,2,4,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_2,2048,2048,10,&uart_Queue,0);

    // char* a = "lalala\n";
    // uart_write_bytes(UART_NUM_2,a,strlen(a));
    s_wifi_event_group = xEventGroupCreate();
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    
    wifi_config_t wifi_config = 
    {
        .sta = 
        {
            .ssid = "SHENTOU",
            .password = "012345678",          
            .threshold.authmode =WIFI_AUTH_OPEN,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
    esp_wifi_start();
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,pdFALSE,pdFALSE,portMAX_DELAY);
    if (bits & WIFI_CONNECTED_BIT)
        ESP_LOGI(TAG, "连接成功!");

    else if (bits & WIFI_FAIL_BIT) 
        ESP_LOGI(TAG, "连接失败!");
    //esp_netif_create_default_wifi_ap();

    // wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();  
    // ESP_ERROR_CHECK(esp_wifi_init(&cfg));          
    // esp_wifi_set_mode(WIFI_MODE_AP);              

    // wifi_config_t wifi_cfg = {                     
    //     .ap =
    //     {
    //         .ssid="Ciallo~(∠・ω＜)⌒☆\0",
    //         .password="012345678",
    //         .ssid_len =strlen(&((&((&wifi_cfg)->ap))->ssid)),
    //         .channel = 1,
    //         .authmode = WIFI_AUTH_WPA_WPA2_PSK,
    //         .max_connection = 4   
    //     }
    // };
    // esp_wifi_set_config(WIFI_IF_AP,&wifi_cfg);      
    // esp_wifi_start();                           

    
    xTaskCreate(uart_event,"uart_handle",4096,NULL,5,NULL);
    xTaskCreate(tcp_client,"tcp_client_handle",4096,NULL,5,NULL);
    // //usertcp_server();
    // tcp_client();
}


