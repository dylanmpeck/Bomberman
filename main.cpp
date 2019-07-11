/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:32:39 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/10 19:44:39 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGLHelper.hpp"
#include "eDirection.hpp"
#include "AnimatedModelLoader.hpp"
#include "AnimationLoader.hpp"

int main()
{
    OpenGLHelper::initEverything();
    bool quit = false;
    Direction curDirection = None;

    AnimatedModel * entity = AnimatedModelLoader::loadEntity("./resources/model.dae", "./resources/diffuse.png");
    Animation anim = AnimationLoader::loadAnimation("resources/model.dae");
    entity->doAnimation(&anim);




    while (quit == false)
    {
        OpenGLDraw::clearScreen();

        OpenGLInput::gameInput(curDirection);

        if (curDirection == Exit)
            quit = true;
        
        entity->update();

        OpenGLDraw::render(entity);

        OpenGLDraw::swapBuffers();
    }
    delete entity;
    OpenGLHelper::cleanup();
    return (0);
}