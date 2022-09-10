#include "nl_client.h"

unsigned int str_to_int(char *str);
/* Utility functions */
/**
 * Converts the port number from string to interger
 * @param str - port number as string
 * @return port number as integer
 */
unsigned int str_to_port(char *str)
{
    unsigned int port = 0;
    char *ch;
    if (strncmp(str, "*", 1) == 0)
    {
        return port;
    }
    // port = (unsigned int)simple_strtol(str, &ch, 10);
    port = str_to_int(str);
    return port;
}

/**
 * Converts the ip address from string to interger
 * @param str - ip address as string
 * @return ip address as integer
 */
unsigned int str_to_ip(char *str, int len)
{
    unsigned int ip = 0;
    int i = 0, j = 0;
    char quad1[4], quad2[4], quad3[4], quad4[4];
    unsigned int q1, q2, q3, q4;
    char *ch;

    if (strncmp(str, "*", 1) == 0)
    {
        return ip;
    }

    while ((str[i] != '.') && (i < len))
    {
        quad1[j++] = str[i++];
    }
    quad1[j] = '\0';
    j = 0;
    i++;
    while ((str[i] != '.') && (i < len))
    {
        quad2[j++] = str[i++];
    }
    quad2[j] = '\0';
    j = 0;
    i++;
    while ((str[i] != '.') && (i < len))
    {
        quad3[j++] = str[i++];
    }
    quad3[j] = '\0';
    i++;
    j = 0;
    while (i < len)
    {
        quad4[j++] = str[i++];
    }
    quad4[j] = '\0';

    // q1 = (unsigned int)simple_strtol(quad1, &ch, 10);
    q1 = str_to_int(quad1);
    q2 = str_to_int(quad2);
    q3 = str_to_int(quad3);
    q4 = str_to_int(quad4);

    q1 *= 16777216;
    q2 *= 65536;
    q3 *= 256;
    ip = q1 + q2 + q3 + q4;

    return ip;
}

void port_to_str(unsigned int port, char *str)
{
    if (!port)
        sprintf(str, "*");
    else
        sprintf(str, "%u", port);
}

void ip_to_str(unsigned int ip, char *str)
{
    unsigned int quad1, quad2, quad3, quad4;
    if (!ip)
        sprintf(str, "*");
    else
    {
        quad1 = ip / 16777216;
        quad2 = (ip - (quad1 * 16777216)) / 65536;
        quad3 = (ip - (quad1 * 16777216) - (quad2 * 65536)) / 256;
        quad4 = ip - (quad1 * 16777216) - (quad2 * 65536) - (quad3 * 256);
        sprintf(str, "%u.%u.%u.%u", quad1, quad2, quad3, quad4);
    }
}

unsigned int str_to_int(char *str)
{
    unsigned int num = 0;
    int i = 0;
    for (i = 0; i < strlen(str); i++)
    {
        num = num * 10 + (str[i] - '0');
    }
    return num;
}
