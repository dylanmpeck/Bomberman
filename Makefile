NAME = test
SOURCE = AnimatedModel.cpp\
		 AnimatedModelLoader.cpp \
		 Animation.cpp \
		 AnimationLoader.cpp \
		 ColladaParser/ColladaLoader/AnimationLoader.cpp \
		 ColladaParser/ColladaLoader/ColladaLoader.cpp \
		 ColladaParser/ColladaLoader/GeometryLoader.cpp \
		 ColladaParser/ColladaLoader/SkeletonLoader.cpp \
		 ColladaParser/ColladaLoader/SkinLoader.cpp \
		 ColladaParser/DataStructures/AnimatedModelData.cpp \
		 ColladaParser/DataStructures/AnimationData.cpp \
		 ColladaParser/DataStructures/JointData.cpp \
		 ColladaParser/DataStructures/JointTransformData.cpp \
		 ColladaParser/DataStructures/KeyFrameData.cpp \
		 ColladaParser/DataStructures/MeshData.cpp \
		 ColladaParser/DataStructures/SkeletonData.cpp \
		 ColladaParser/DataStructures/SkinningData.cpp \
		 ColladaParser/DataStructures/Vertex.cpp \
		 ColladaParser/DataStructures/VertexSkinData.cpp \
		 Animator.cpp \
		 Callbacks.cpp \
		 Camera.cpp \
		 GLDebug.cpp \
		 IndexBuffer.cpp \
		 Joint.cpp \
		 JointTransform.cpp \
		 OpenGLClock.cpp \
		 OpenGLDraw.cpp \
		 OpenGLHelper.cpp \
		 OpenGLInit.cpp \
		 OpenGLInput.cpp \
		 Quaternion.cpp \
		 ResourceManager.cpp \
		 Shader.cpp \
		 TextRenderer.cpp \
		 Texture.cpp \
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
	  -L/nfs/2018/d/dpeck/.brew/Cellar/freetype/2.9.1/lib
DEPEND = -lfreetype -lfreetype.6 -lglfw -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon


all: $(NAME)

$(NAME):
	g++ -std=c++11 -stdlib=libc++ $(INCLUDES) $(LIB) $(DEPEND) $(SOURCE)

clean:
	/bin/rm -f *.o

flcean: clean
	/bin/rm $(NAME)

re: fclean all
