#include "Renderable.h"

RenderLayer* defaultRenderLayer;

RenderLayer::RenderLayer()
: link(NULL), active(true)
{
}

RenderLayer::RenderLayer(RenderChain* link)
: link(link), active(true)
{
}

void RenderLayer::render(sf::RenderTarget& window)
{
    if (link)
        link->render(window);
    if (active)
        foreach(Renderable, r, renderableList)
            r->render(window);
}

Renderable::Renderable()
{
    layer = defaultRenderLayer;
    if (layer)
        layer->renderableList.push_back(this);
}

Renderable::Renderable(RenderLayer* renderLayer)
{
    layer = renderLayer;
    if (layer)
        layer->renderableList.push_back(this);
}

void Renderable::moveToRenderLayer(RenderLayer* new_render_layer)
{
    if (layer)
        for(unsigned int n=0; n<layer->renderableList.size(); n++)
            if (layer->renderableList[n] == this)
                layer->renderableList[n] = NULL;
    layer = new_render_layer;
    if (layer)
        layer->renderableList.push_back(this);
}
