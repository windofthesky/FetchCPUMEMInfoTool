# FetchCPUMEMInfoTool
The tool which fetch CPU &amp; MEM information on Linux platform.
Compile Note:
compile command:
gcc -o Fetchinfo -L/usr/lib/ -lmysqlclient m_linux.c utils.c Fetchinfo.c

usage:
./Fetchinfo  ServerName  ip
demo: ./Fetchinfo TestServer3  192.168.2.223

所需准备：
1. 从Oracle官方获得mysql-connector-c-6.1.5-linux-glibc2.5-x86_64.tar.gz解压。
2. 将include下的内容放到/usr/include目录下。
3. 将lib下的内容放到/usr/lib目录下。
注：2，3步骤需保持内容目录结构一致！

Fetchinfo.c编译依赖mysql和m_linux,utils,因此需要在编译时指定。


表创建：
CREATE TABLE `cpu` (
  `ServerName` varchar(255) NOT NULL,
  `IP` varchar(30) DEFAULT NULL,
  `CPU_Load` float DEFAULT NULL,
  `Mem_Used` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
