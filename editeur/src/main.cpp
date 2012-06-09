#include <iostream>
#include <cce/Tile.hpp>
#include <edt/Repere.hpp>

int main()
{
    edt::Repere *r = new edt::Repere(5,8);
    std::cout << r->largeur << " " << r->hauteur << std::endl;;
    r->redimensionner(3,6);
    std::cout << r->largeur << " " << r->hauteur << std::endl;;
    return EXIT_SUCCESS;
}
