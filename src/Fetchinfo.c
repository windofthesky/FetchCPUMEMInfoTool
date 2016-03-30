#include <stdio.h>
#include <unistd.h>
#include <mysql.h>
#include "machine.h"

int machine_init(struct statics * statics);
void get_system_info(struct system_info *info);
void read_one_proc_stat(pid_t pid, struct top_proc *proc);
char *format_next_process(struct top_proc *p);

int main(int argc,char *argv[])
{
    float CPU_Usage = 0.0;
    int MEM_Usage = 0;
    int MEM_Total = 0; 
    int result = 0;
    struct statics stat;
    struct system_info info;
    MYSQL mysql;

    machine_init(&stat);
    get_system_info(&info);
    
    do
    {
        mysql_init(&mysql);
        CPU_Usage = ((float)info.cpustates[0]/10) + ((float)info.cpustates[2]/10);
	MEM_Usage = info.memory[0]-info.memory[1];
	MEM_Total = info.memory[0];
        
        char cpu_usg[6];
        sprintf(cpu_usg, "%.1f", CPU_Usage);
        char mem_usg[8];
        sprintf(mem_usg, "%d", MEM_Usage);
        char mem_total[8];
        sprintf(mem_total, "%d", MEM_Total);
        
        //test code
	//printf("cpu usage: %s", cpu_usg);
        //printf("mem usage: %s", mem_usg);
        //printf("mem total: %s", mem_total);
        //INSERT INTO cpu(ServerName, ip, CPU_Load, Mem_Used) VALUES('TestServer1', '192.xx.xx.xx', 0.5 , 656896)
        if(mysql_real_connect(&mysql,"192.168.2.7","root","123456","test",0,NULL,0) && strlen(mem_usg) > 0)
        {
	    char query_insert[150];
            char *query = "INSERT INTO cpu(ServerName, ip, CPU_Load, Mem_Used) VALUES('";
            char *server = argv[1];//"TestServer1";
	    char *ip = argv[2];
            char *intev1 = "', '";
	    char *intev2 = "', ";
	    char *intev3 = " , ";
            char *intev4 = ")";
            strcpy(query_insert, query);
	    strcat(query_insert, server);
	    strcat(query_insert, intev1);
	    strcat(query_insert, ip);
	    strcat(query_insert, intev2);
	    strcat(query_insert, cpu_usg);
	    strcat(query_insert, intev3);
	    strcat(query_insert, mem_usg);
	    strcat(query_insert, intev4);

	    //test code
            //printf("Insert command is : %s \n", query_insert);
            //insert the collected information into mysql table.
            result = mysql_query(&mysql, query_insert);
	}
        sleep(10);	
    }while(1);
    
    return 0;
}
