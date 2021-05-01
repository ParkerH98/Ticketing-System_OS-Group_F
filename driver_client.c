#include "parker_client.c"
#include "parker_utility.c"
#include "rasheed.c"

// Usage Instructions:
// make c && ./c

int main()
{
    int port = randomPort(PORT, PORT + NUM_SERVERS - 1);

    clientSocket_SendReceive(port);
    return 0;
}