#include "memory.h"

Header *memory_ptr = &_end; // fin du programme (et début du tas)
static Header* nextFreeMemory;
static Header* base = NULL;
static int nbPlace = 0;
static int sizeM = 0;

void * operator new(size_t size) throw()
{
    nbPlace++;
    if (base == NULL)
    {
        base = memory_ptr;
        base->s.nextFree = memory_ptr;
        #ifdef STM32F10X_MD // stm h103
        base->s.size = 5000;   // Initialisation de la mémoire = Taille disponible dans la ram en unit de base de la mémoire (une unité = 4 octets). Ici 20kB -> 5000 unit
        #endif
        #ifdef STM32F10X_CL // stm h107
        base->s.size = 16000;   // Initialisation de la mémoire = Taille disponible dans la ram en unit de base de la mémoire (une unité = 4 octets). Ici 64kB -> 16000 unit
        #endif
        nextFreeMemory = memory_ptr;

    }
    unsigned nunit = (size + sizeof(Header)-1)/sizeof(Header)+1;
    sizeM += nunit;
    Header *p = nextFreeMemory;
    Header  *oldP = p;
    Header *ip;
    for (ip = nextFreeMemory; ; p = ip, ip = ip->s.nextFree)
    {
        if (nunit <= ip->s.size )
        {
            if (nunit == ip->s.size)
            {
                if (ip->s.nextFree != ip)
                {
                    nextFreeMemory = ip->s.nextFree;
                }
                else
                {
                    nextFreeMemory = NULL;
                }
            }
            else
            {
                unsigned oldFreeUnit = p->s.size;
                p->s.size = nunit;
                oldP = p;
                p += nunit;
                oldP->s.nextFree = p;
                p->s.size = oldFreeUnit - nunit;
                p->s.nextFree = p;
                if (ip == nextFreeMemory)
                {
                   nextFreeMemory = p;
                }
            }

            return ip+1;
        }
        if (ip==oldP)
        {
            return NULL;
        }
    }
}

void * operator new[](size_t size) throw()
{
  return operator new(size);
}

void operator delete(void * p)    throw()
{
    nbPlace--;
    Header* d = (Header*)p -1;
    sizeM -= d->s.size;
    Header* predFree;
    for(predFree = nextFreeMemory;  !((d > predFree)&&(d<predFree->s.nextFree)); predFree = predFree->s.nextFree )
    {
        if(predFree>=predFree->s.nextFree && (d > predFree || d<predFree->s.nextFree))
        break;
    }

    if ( d + d->s.size == predFree->s.nextFree ) // si le prochain vide est collé au block libéré
    {
        d->s.size += predFree->s.nextFree->s.size;
        d->s.nextFree = predFree->s.nextFree->s.nextFree;
    }
    else
    {
        d->s.nextFree = predFree->s.nextFree;
    }
    if (predFree+predFree->s.size == d)
    {
        predFree->s.nextFree = d->s.nextFree;
        predFree->s.size += d->s.size;
    }
    else
    {
        predFree->s.nextFree = d;
    }
    nextFreeMemory = predFree;

  /*  d--; // d est maintenant le Header de la zone mémoire contenant l'objet que l'on delete
    d->s.nextFree = nextFreeMemory; // On indique que la prochaîne mémoire vide sera la première mémoire vide au moment où on a lancé le delete
    nextFreeMemory = d;
    */
}

void operator delete[](void * p)    throw()
{
    return operator delete(p);
}
