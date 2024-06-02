import socket
import threading


command = None

client_class = ['esp32','mobile_terminal','desktop_terminal']  #注册设备列表

device= {}  #已连接设备

cmd_threads = {}

command_class = ['start','stop','exit','list','reset']  #服务器命令列表


client_cmd_class = [
    'f'
]

server = None

class connected_device:
    def __init__(self,name : str,ss:socket) -> None:
        self.name = name
        self.socket = ss
        self.thread = None

class cmd_thread:
    def __init__(self,name : str,) -> None:
        self.name = name
        


def execute(cmd : str):
    if  cmd in command_class:
        if cmd == 'start':
            port = 0
            port =input("输入监听端口:")
            cmd_threads[cmd] = cmd_thread(cmd)
            cmd_threads[cmd].thread = threading.Thread(target= server_start,args=(port,))
            cmd_threads[cmd].thread.start()
        elif cmd == 'stop':
            ...
        elif cmd == 'exit':
            ...
        elif cmd == 'list':
            for i in device:
                print(f"已连接设备:{device[i].name}")
        elif cmd == 'reset':
            ...

    else:
        print('错误的指令!')

def get_host_ip():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        address = ("8.8.8.8", 80)
        s.connect(address)
        sockname = s.getsockname()
        ip = sockname[0]
        
    finally:
        s.close()
    return ip
    


def client_thread(self : connected_device):
    while True:   
        receive = self.socket.recv(1024).decode()  
        client_cmd = receive[:1]
        client_cmd_var = int(receive[1:2])
        

        client_data = receive[2:]
        if client_cmd in client_cmd_class:
            if client_cmd == 'f':
                if client_cmd_var in device:
                    device[client_cmd_var].socket.send(client_data.encode())
                else:
                    print(f"来自{self.name}  到{client_class[client_cmd_var]}的转发请求失败!  {client_data}")

        else:
            print(f"来自{self.name},参数错误")


        if client_data == "exit":       # 判断是否退出连接
            exit("通信结束")
        
    



def server_start(port :str):
    global server
    ip = get_host_ip()
    if server is None:
        print(f"服务器已在运行\nip:{ip}")
    
    ip_port = (ip,int(port))
    server = socket.socket()            # 创建套接字
    server.bind(ip_port)
    server.listen(5)
    print("socket初始化完成\n等待连接...")
    while(True):
        try:
            client, addr = server.accept()
            head = client.recv(1024).decode()
            if head in client_class:
                print(f"{head}成功连接到服务器")
                new_device = connected_device(head,client)
                new_device.thread = threading.Thread(target=client_thread,args=(new_device,))
                new_device.thread.start()
                device[client_class.index(head)] = new_device
            else:
                client.close()
                print(f"{addr}被拒绝连接")

        except Exception as e:
            print(e)
            continue
        




if __name__ == '__main__':
    print("已启动，请输入指令")
    while True:
        command = input()
        execute(command)