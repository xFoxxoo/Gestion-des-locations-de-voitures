#include "menu.h"
#include "data.h"

int main()
{
    Nc *lc = NULL;
    Nv *lv = NULL;
    Nr *lr = NULL;

    /* Uncomment the line below to load test data for testing */
    /* InitTestData(&lc, &lv, &lr); */

    MenuPrincipal(&lc, &lv, &lr);

    return 0;
}