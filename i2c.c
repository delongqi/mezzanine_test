#include <stdio.h>  
#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <string.h>  
  
#define CHIP_ADDR 0x68 
#define I2C_DEV "/dev/i2c-0"//i2c_dev为i2c　adapter创建的别名  
//读操作先发Slaveaddr_W+Regaddr_H+Regaddr_L 3个字节来告诉设备操作器件及两个byte参数  
//然后发送Slaveaddr_R读数据  
static int iic_read(int fd, char buff[], int addr, int count)  
{  
    int res;  
    char sendbuffer1[2];  
    sendbuffer1[0]=addr>>8;  
    sendbuffer1[1]=addr;  
    write(fd,sendbuffer1,2);        
    res=read(fd,buff,count);  
    printf("read %d byte at 0x%x/n", res, addr);  
    return res;  
}  
//在写之前，在数据前加两个byte的参数，根据需要解析  
static int iic_write(int fd, char buff[], int addr, int count)  
{  
    int res;  
    int i,n;  
    static char sendbuffer[100];  
    memcpy(sendbuffer+2, buff, count);  
    sendbuffer[0]=addr>>8;  
    sendbuffer[1]=addr;  
    res=write(fd,sendbuffer,count+2);  
    printf("write %d byte at 0x%x/n", res, addr);  
}

void setDateDs1307(int fd)
{
    char buf[1];
    char data[7] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07};
    buf[0] = 0x00;
    iic_write(fd,buf,CHIP_ADDR,1);
    usleep(10000);
    iic_write(fd,data,CHIP_ADDR,7);
    usleep(10000);
}
 
void getDateDs1307(int fd)
{
    char buf[1]={0x00};
    char value[7];
    iic_write(fd,buf,CHIP_ADDR,1);
    iic_read(fd,value,CHIP_ADDR,7);
    usleep(50000);
} 
int main(void)
{  
    int fd;  
    fd = open(I2C_DEV, O_RDWR);// I2C_DEV /dev/i2c-0  
    if(fd < 0)
    {  
        printf("####i2c test device open failed####/n");  
        return (-1);  
    }
    setDateDs1307(fd);
    getDateDs1307(fd);  
    return 0;  
}  
