/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:32:39 by dpeck             #+#    #+#             */
/*   Updated: 2019/07/12 18:05:25 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGLHelper.hpp"
#include "eDirection.hpp"
#include "AnimatedModelLoader.hpp"
#include "AnimationLoader.hpp"
#include "ResourceManager.hpp"
#include "ModelImporting/Model.hpp"

int main()
{
    OpenGLHelper::initEverything();
    bool quit = false;
    Direction curDirection = None;

    //AnimatedModel * entity = AnimatedModelLoader::loadEntity("./resources/model.dae", "./resources/diffuse.png");
    //Animation anim = AnimationLoader::loadAnimation("resources/model.dae");
    //entity->doAnimation(&anim);

    Shader * shader = &ResourceManager::getShader("modelLoadingShader");

    Model model("resources/nanosuit/nanosuit.obj");


    while (quit == false)
    {
        OpenGLDraw::clearScreen();

        OpenGLInput::gameInput(curDirection);

        if (curDirection == Exit)
            quit = true;

        shader->bind();

        model.draw(shader);
        
        //entity->update();

        //OpenGLDraw::render(entity);

        OpenGLDraw::swapBuffers();
    }
    //delete entity;
    OpenGLHelper::cleanup();
    return (0);
}