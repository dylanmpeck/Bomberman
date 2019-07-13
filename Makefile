NAME = test
SOURCE = Callbacks.cpp \
		 Camera.cpp \
		 GLDebug.cpp \
		 IndexBuffer.cpp \
		 Joint.cpp \
		 JointTransform.cpp \
		 ModelImporting/Mesh.cpp \
		 ModelImporting/Model.cpp \
		 OpenGLClock.cpp \
		 OpenGLDraw.cpp \
		 OpenGLHelper.cpp \
		 OpenGLInit.cpp \
		 OpenGLInput.cpp \
		 Quaternion.cpp \
		 ResourceManager.cpp \
		 Shader.cpp \
		 TextRenderer.cpp \
		 TextureLoader.cpp \
		 VertexArray.cpp \
		 VertexBuffer.cpp \
		 glad.cpp \
		 main.cpp \
		 pugixml/src/pugixml.cpp\
		 vendor/stb_image/stb_image.cpp
INCLUDES = 	-I /nfs/2018/d/dpeck/bomberman/include\
			-I /nfs/2018/d/dpeck/bomberman/freetype\
			-I /nfs/2018/d/dpeck/bomberman\
           	-I /nfs/2018/d/dpeck/bomberman/ColladaParser\
		   	-I/nfs/2018/d/dpeck/.brew/Cellar/glfw/3.3/include
LIB = -L/nfs/2018/d/dpeck/.brew/Cellar/glfw/3.3/lib \
	  -L/nfs/2018/d/dpeck/.brew/Cellar/freetype/2.9.1/lib\
	  -L/nfs/2018/d/dpeck/.brew/Cellar/assimp/4.1.0/lib
DEPEND = -lassimp.4.1.0 -lIrrXML -lfreetype -lfreetype.6 -lglfw -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon


all: $(NAME)

$(NAME):
	g++ -g -fsanitize=address -fno-omit-frame-pointer -std=c++11 -stdlib=libc++ $(INCLUDES) $(LIB) $(DEPEND) $(SOURCE)

clean:
	/bin/rm -f *.o

flcean: clean
	/bin/rm $(NAME)

re: fclean all
