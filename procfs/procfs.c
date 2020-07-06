#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
 
#define FILE_NAME    "procfs"
#define FILE_SIZE    100
 
struct data_t
{
    char value[FILE_SIZE + 1];
}netstat;
 
static struct proc_dir_entry *netstat_file;
 
/* proc file에 데이터를 쓰는 함수 */
static ssize_t write(struct file *file, const char *buf,
        size_t count, loff_t *pos)
{
    int len;
    len = (count > FILE_SIZE) ? FILE_SIZE : count;
    /* raw_copy_from_user? -> copy_from_user함수의 function chaining에 연결됨 */
    if (raw_copy_from_user(netstat.value, buf, len))    //write 실패시 error return
        return -EFAULT; // address error
    netstat.value[len] = 0x00;
    printk("%s count:%ld\n", netstat.value, count);
 
    return len;
}
 
/* proc file을 읽을 경우 실행되는 함수 */
static int proc_show(struct seq_file *m, void *v) 
{
//    printk("%s\n", (char *)m->private);
    seq_printf(m, "%s", netstat.value); // 출력 형식
    return 0;
}
    
static int proc_open(struct inode *inode, struct  file *file)
{
//    return single_open(file, proc_show, "private_data");
    return single_open(file, proc_show, NULL);
}

// file_operations 구조체 초기화
// c99 버전부터 아래와 같은 방식으로 초기화 가능
static const struct file_operations proc_fops = { 
    .owner = THIS_MODULE,
     //파일을 열때 불려지는 함수
    .open = proc_open,
     // 파일을 읽을때 불려지는 함수
    .read = seq_read,
     // 파일을 쓸때 불려지는 함수
    .write = write,
    .llseek = seq_lseek,
    .release = single_release,
}; 

/* module 적재 함수 */
static int mod_procfs_init(void)
{
    strcpy(netstat.value, ""); //proc file 초기값
 
    // procfs 파일 생성
    netstat_file = proc_create(FILE_NAME, 0646, NULL, &proc_fops);
                          //파일이름, 퍼미션, 디렉토리, file_operations 구조체
    if(netstat_file == NULL){   //proc file 생성 실패경우 
        printk("netsat_file: error \n");
        return -EEXIST;
    }
 
	// 시스템 로그에 mod_procfs_init 출력
    printk("%s\n", __FUNCTION__);
    return 0;
}

/* 모듈 제거 함수 */
static void mod_procfs_exit(void){
    // 디렉토리, 파일 삭제
    remove_proc_entry(FILE_NAME, NULL);
                               // 파일이 위치하고있는 디렉토리
    remove_proc_entry(NULL, NULL);

	// 시스템 로그에 mod_procfs_exit 출력
    printk("%s\n", __FUNCTION__);
}
 
module_init(mod_procfs_init);
module_exit(mod_procfs_exit);
