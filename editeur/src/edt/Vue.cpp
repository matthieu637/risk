#include "edt/Vue.hpp"
#include "edt/GUI.hpp"

#include "bib/Logger.hpp"
#include <cce/MoteurSFML.hpp>
#include "edt/Console.hpp"
#include <CEGUI/elements/CEGUIScrollbar.h>
#include <CEGUI/elements/CEGUIThumb.h>

namespace edt {

Vue::Vue(cce::MoteurSFML* engine, GUI* gui) : cce::Vue(engine, gui)
{

}

Vue::~Vue()
{

}

void Vue::updateCameraPosition(int x, int y)
{
    cce::Vue::updateCameraPosition(x,y);
}

GUI* Vue::getGUI()
{
    return (GUI*)gui;
}

void Vue::updateListRegions(list<string> noms)
{
    getGUI()->updateListRegions(noms);
}

void Vue::updateYCamera(int y)
{
    sf::View* v = engine->getView();
    v->setCenter(v->getCenter().x, y);
}

void Vue::updateXCamera(int x) {
    sf::View* v = engine->getView();
    v->setCenter(x, v->getCenter().y);
}

void Vue::updateScrolls()
{
    sf::View* camera = engine->getView();
    CEGUI::Scrollbar* vert = static_cast<CEGUI::Scrollbar*>(getGUI()->getRootWindow()->getChild("Editeur/VSB"));
    vert->setScrollPosition(camera->getCenter().y);

    CEGUI::Scrollbar* hori = static_cast<CEGUI::Scrollbar*>(getGUI()->getRootWindow()->getChild("Editeur/HSB"));
    hori->setScrollPosition(camera->getCenter().x);
}

void Vue::quit()
{
   if(getGUI()->getConsole()->getConfirmQuit()){
	engine->getFenetre()->close();
   }
}


void Vue::initScrolls(int largeur, int hauteur)
{
    getGUI()->initScrollPane(largeur, hauteur);
}

void Vue::updateScrollsThumb(float coef, int largeur, int hauteur)
{

    float min_thumb = 0.03;
    float max_thumb = 0.95;

    float hmin_zoom = 0.1*hauteur;
    float hmax_zoom = 5*hauteur;
    float vmin_zoom = 0.1*largeur;
    float vmax_zoom = 5*largeur;

    float hcoef = coef*hauteur;
    float vcoef = coef*largeur;

    if(hcoef > hmax_zoom)
        hcoef = hmax_zoom;
    else if(hcoef < hmin_zoom)
        hcoef = hmin_zoom;

    if(vcoef > vmax_zoom)
        vcoef = vmax_zoom;
    else if(vcoef < vmin_zoom)
        vcoef = vmin_zoom;

    CEGUI::Scrollbar* vert = static_cast<CEGUI::Scrollbar*>(getGUI()->getRootWindow()->getChild("Editeur/VSB"));
    CEGUI::Thumb* vtumb = vert->getThumb();
    CEGUI::URect vtarea = vtumb->getArea();
    vtarea.setHeight(CEGUI::UDim(((hcoef-hmin_zoom)/(hmax_zoom - hmin_zoom))*(max_thumb-min_thumb) + min_thumb, 0.));
    vtumb->setArea(vtarea);


    CEGUI::Scrollbar* hori = static_cast<CEGUI::Scrollbar*>(getGUI()->getRootWindow()->getChild("Editeur/HSB"));
    CEGUI::Thumb* htumb = hori->getThumb();
    CEGUI::URect htarea = htumb->getArea();
    htarea.setWidth(CEGUI::UDim(((vcoef-vmin_zoom)/(vmax_zoom - vmin_zoom))*(max_thumb-min_thumb) + min_thumb, 0.));
    htumb->setArea(htarea);

    updateScrolls();
}

void Vue::updateCameraZoom(float factor)
{
    cce::Vue::updateCameraZoom(factor);
}

void Vue::updateSize(int width, int height)
{
    CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Size(width, height));
}

void Vue::reloadGUI()
{
    getGUI()->deleteGUI();
    getGUI()->loadCustomGUI();
}

}
