#include <dns.h>
#include <stdio.h>


int main()
{
    struct dns_answers *cur;
    const char         *server = "8.8.8.8"; /* place your favourite one */
    struct dns_answers *ans    = dns_get(server, "veresov.pro", dns_type_txt);
    for (cur = ans; cur; cur = cur->next) {
        if (cur->type == dns_type_a) {
            unsigned char *ip = cur->data;
            printf("IP address of %s is %d.%d.%d.%d.\n",
                   cur->host, ip[0], ip[1], ip[2], ip[3]);
        } else if (cur->type == dns_type_cname) {
            printf("Cannonical name of %s is %s.\n", cur->host, cur->data);
        } else if (cur->type == dns_type_txt) {
            printf("Text from %s: %s\n", cur->host, cur->data);
        } else if (cur->type == dns_type_srv) {
            printf("Service %s is located at %s on port %d "
                   "with priority %d and weight %d.\n",
                   cur->host,
                   dns_srv_server(cur->data),   dns_srv_port(cur->data),
                   dns_srv_priority(cur->data), dns_srv_weight(cur->data));
        } else if (cur->type == dns_type_mx) {
            printf("Mail exchange server for %s with preference %d is %s.\n",
                   cur->host,
                   dns_mx_preference(cur->data), dns_mx_server(cur->data));
        }
    }
    dns_free(ans);
    return 0;
}
