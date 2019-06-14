#include <linux/fs.h>
#include <linux/init.h>
#include <linux/pid_namespace.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/seqlock.h>
#include <linux/time.h>
#include <linux/module.h>

#include <linux/kernel.h>
#include <linux/hrtimer.h>
#include <linux/jiffies.h>

#define LOAD_INT(x) ((x) >> FSHIFT)
#define LOAD_FRAC(x) LOAD_INT(((x) & (FIXED_1-1)) * 100)

static struct hrtimer timer;
ktime_t kt;

static enum hrtimer_restart        hrtimer_hander(struct hrtimer *timer)
{
    printk("yangfei:I am in hrtimer hander\r\n");

    hrtimer_forward(timer,timer->base->get_time(),kt);

    return HRTIMER_RESTART;
        

}
static int loadavg_proc_show(struct seq_file *m, void *v)
{
	unsigned long avnrun[3];

	get_avenrun(avnrun, FIXED_1/200, 0);

	seq_printf(m, "%lu.%02lu %lu.%02lu %lu.%02lu %ld/%d %d\n",
		LOAD_INT(avnrun[0]), LOAD_FRAC(avnrun[0]),
		LOAD_INT(avnrun[1]), LOAD_FRAC(avnrun[1]),
		LOAD_INT(avnrun[2]), LOAD_FRAC(avnrun[2]),
		nr_running(), nr_threads,
		task_active_pid_ns(current)->last_pid);
	return 0;
}

static int loadavg_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, loadavg_proc_show, NULL);
}

static const struct file_operations loadavg_proc_fops = {
	.open		= loadavg_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init my_proc_loadavg_init(void)
{
	proc_create("my_loadavg", 0, NULL, &loadavg_proc_fops);
	
	printk("yangfei:---------%s-----------\r\n",__func__);
    	kt = ktime_set(0,1000000000);
    	hrtimer_init(&timer,CLOCK_MONOTONIC,HRTIMER_MODE_REL);
    	hrtimer_start(&timer,kt,HRTIMER_MODE_REL);
    	timer.function = hrtimer_hander;
	
	return 0;
}
fs_initcall(my_proc_loadavg_init);

MODULE_LICENSE("GPL");
