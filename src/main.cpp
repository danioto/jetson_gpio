#include <gpio.h>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <sys/signal.h>

static struct termios oldt, newt;
gpio_pin pin;

void clean_and_exit(int code);
extern "C" void quit_signal_handler(int signum);

int main (int argc, char **argv)
{
    // help variables
    int c;

    // tty settings
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    // open pin
    if (gpio_open_dir(&pin, 57, GPIO_OUT))
    {
        fprintf(stderr, "open testpin failed\n");
        clean_and_exit(-1);
        std::exit(-1);
    }

    //Kill signal handler
    signal(SIGINT,quit_signal_handler);

    // loop
    while ((c=getchar())!= 'q')
    {
        if (c=='0')
        {
            gpio_set_value(&pin, GPIO_LOW);
            printf("Pin is sober!\n\r");
        } else if (c=='1')
        {
            gpio_set_value(&pin, GPIO_HIGH);
            printf("Pin is high!\n\r");
        } else printf("Press 1 or 0 or q.\n\r");
    }

    // cleanup
    printf("Will end now!\n");
    clean_and_exit(0);
}

void clean_and_exit(int code)
{
    // clean gpio
    if (gpio_close(&pin)) fprintf (stderr, "close testpin failed\n");
    gpio_destroy();

    // tty reset settings
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

    // exit
    std::exit(code);
}

void quit_signal_handler(int signum)
{
    printf("Will end now!\n");
    clean_and_exit(0);
}
