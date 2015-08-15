#include "glwidget.h"
#include "objModel.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtx/transform.hpp"

#include <iostream>
#include <vector>

#include <QCoreApplication>
#include <QKeyEvent>
#include <stdexcept>
#include <QMenuBar>
#include <QFileDialog>
#include <QLabel>

#define VERT_SHADER ":/simple.vert"
#define FRAG_SHADER ":/simple.frag"

QMenuBar* mainMenu;
QMenu* fileMenu;
QAction* openAction;
QAction* resetAction;
QLabel* modeLabel;

bool shadersLoaded = false;

float transStep = 0.2f;
float rotStep = 12.0f;
float scaleStep = 0.5f;
float lightRotStep = 12.0f;

glm::mat4 translationMat, rotationMat, scaleMat, lightRotationMat;
glm::mat4 modelMat, view, projection;

std::vector<std::string> axes = {"x-axis", "y-axis", "z-axis"};
uint activeAxis = 0; //x=0, y=1, z=2
uint activeTransformation = 0; //translate=0, rotate=1, scale=2, rotateLights=3

//lighting related veriables
float k_ambient = 1.0f;
const int numLights = 2;
std::vector<float> lightPositions = {
    2.0f, 2.0f, 4.0f,
    -1.0f, 1.0f, -3.0f
};
std::vector<float> lightIntensities = {
    0.2f, 0.4f, 0.2f,
    0.4f, 0.2f, 0.2f
};

//tecture related variables
std::vector<float> textureData;
uint textureWidth = 0, textureHeight = 0;

//constructor
GLWidget::GLWidget( const QGLFormat& format, QWidget* parent )
    : QGLWidget( format, parent ),
      m_vertexBuffer( QOpenGLBuffer::VertexBuffer ),
      red(1.0f),
      green(0.0f),
      blue(0.0f),
      model_filename("")
{
    //set up the menu bar
    mainMenu = new QMenuBar(this);
    fileMenu = new QMenu("File");
    openAction = fileMenu->addAction("Open");
    QObject::connect(openAction, SIGNAL(triggered()), this, SLOT(handle_open_clicked()));
    resetAction = fileMenu->addAction("New/Reset");
    QObject::connect(resetAction, SIGNAL(triggered()), this, SLOT(handle_reset_clicked()));
    mainMenu->addMenu(fileMenu);
}

//slots --------------------------------------------------------

//slot for Open action in the File menu
bool GLWidget::handle_open_clicked(){
    std::cout << "open" << std::endl;

    //show an open file dialog and get the selected file name
    model_filename = QFileDialog::getOpenFileName(this, tr("Open obj model"), "~", "Obj files (*.obj)").toStdString();

    //run intialiseGL to reset the scene and load up the new model
    initializeGL();
    return true;
}

//slot for reset action in the File menu
bool GLWidget::handle_reset_clicked(){
    std::cout << "reset" << std::endl;

    //run intialiseGL to reload the current  and reset the scene
    initializeGL();
    return true;
}

//slot for wheelEvent. Performs current ActiveTransformation in ActiveAxis on the model
void GLWidget::wheelEvent(QWheelEvent * evt){
    int delta = evt->delta();
    int dir = glm::abs(delta) / delta; //gets +1 or -1 based on direction scrolling

    //do the correct transformation
    switch(activeTransformation){
        //translate model
        case 0:
            if(activeAxis == 0){
                translateModel(glm::vec3(dir * transStep, 0.0f, 0.0f));
                QWidget::setWindowTitle("Prac4: Translating model in x-axis");
            }else if(activeAxis == 1){
                translateModel(glm::vec3(0.0f, dir * transStep, 0.0f));
                QWidget::setWindowTitle("Prac4: Translating model in y-axis");

            }else{
                translateModel(glm::vec3(0.0f, 0.0f, dir * transStep));
                QWidget::setWindowTitle("Prac4: Translating model in z-axis");
            }
            break;

        //rotate model
        case 1:
            if(activeAxis == 0){
                rotateModel(glm::vec3(1.0f, 0.0f, 0.0f), dir * rotStep);
                QWidget::setWindowTitle("Prac4: Rotating model in x-axis");
            }else if(activeAxis == 1){
                rotateModel(glm::vec3(0.0f, 1.0f, 0.0f), dir * rotStep);
                QWidget::setWindowTitle("Prac4: Rotating model in y-axis");
            }else{
                rotateModel(glm::vec3(0.0f, 0.0f, 1.0f), dir * rotStep);
                QWidget::setWindowTitle("Prac4: Rotating model in z-axis");
            }
            break;

        //scale
        case 2:
            if(activeAxis == 0){
                scaleModel(glm::vec3((dir * scaleStep) + 1.0f, 1.0f, 1.0f));
                QWidget::setWindowTitle("Prac4: Scaling model in x-axis");
            }else if (activeAxis == 1){
                scaleModel(glm::vec3(1.0f, (dir * scaleStep) + 1.0f, 1.0f));
                QWidget::setWindowTitle("Prac4: Scaling model in y-axis");
            }else{
                scaleModel(glm::vec3(1.0f, 1.0f, (dir * scaleStep) + 1.0f));
                QWidget::setWindowTitle("Prac4: Scaling model in z-axis");
            }
            break;

        //rotate lights
        case 3:
            rotateLights(dir * lightRotStep);
            break;
    }

    //update the scene
    updateGL();
}

//handles keyPress input
void GLWidget::keyPressEvent( QKeyEvent* e )
{
    switch ( e->key() )
    {
        case Qt::Key_Escape:
            QCoreApplication::instance()->quit();
            break;

        case Qt::Key_1:
            //std::cout << "change col 1" << std::endl;
            setRenderColor(1);
            break;

        case Qt::Key_2:
            //std::cout << "change col 2" << std::endl;
            setRenderColor(2);
            break;

        case Qt::Key_3:
            //std::cout << "change col 3" << std::endl;
            setRenderColor(3);
            break;

        case Qt::Key_4:
            //std::cout << "change col 4" << std::endl;
            setRenderColor(4);
            break;

        case Qt::Key_5:
            //std::cout << "change col 5" << std::endl;
            setRenderColor(5);
            break;

        case Qt::Key_T:
            incrementActiveAxis();
            activeTransformation = 0;
            QWidget::setWindowTitle(QString::fromStdString("Prac4: Translating model in " + axes[activeAxis]));
            break;

        case Qt::Key_R:
            incrementActiveAxis();
            activeTransformation = 1;
            QWidget::setWindowTitle(QString::fromStdString("Prac4: Rotating model in " + axes[activeAxis]));
            break;

        case Qt::Key_S:
            incrementActiveAxis();
            activeTransformation = 2;
            QWidget::setWindowTitle(QString::fromStdString("Prac4: Scaling model in " + axes[activeAxis]));
            break;

        case Qt::Key_L:
            activeTransformation = 3;
            QWidget::setWindowTitle(QString::fromStdString("Prac4: Rotating lights around scene"));
            break;

        default:
            QGLWidget::keyPressEvent( e );
    }
}




//helpers-------------------------------------------------------------------------------

//loads in the model at location model_filename
void GLWidget::loadModel(){
    // we need a VAO in core!
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // We need us some vertex data.
    const char* fn = model_filename.c_str();
    obj.read(fn);

    m_vertexBuffer.create();
    m_vertexBuffer.setUsagePattern( QOpenGLBuffer::StaticDraw );
    if ( !m_vertexBuffer.bind() )
    {
        qWarning() << "Could not bind vertex buffer to the context";
        return;
    }
    m_vertexBuffer.allocate(&obj.vertices[0], obj.vertices.size() * sizeof( glm::vec3 ) );


    //shaders can only be loaded once. Don't want to run the code if we have already loaded
    //the shaders.
    if(!shadersLoaded){
        qDebug() << "Attempting vertex shader load from " << VERT_SHADER;
        qDebug() << "Attempting fragment shader load from " << FRAG_SHADER;

        // Prepare a complete shader program...
        if ( !prepareShaderProgram( VERT_SHADER, FRAG_SHADER) )
            std::runtime_error("Failed to load shader");

        shadersLoaded = true;
    }

    // Bind the shader program so that we can associate variables from
    // our application to the shaders
    if ( !m_shader.bind() )
    {
        qWarning() << "Could not bind shader program to context";
        return;
    }

    // Enable the "vertex" attribute to bind it to our currently bound
    // vertex buffer.
    m_shader.setAttributeBuffer( "vertex", GL_FLOAT, 0, 3 );
    m_shader.enableAttributeArray( "vertex" );

    setRenderColor(0); //setting the default render colour

    //pass the normal and uv vertex attribute data through to the shader
    GLuint normals_vbo = 0;
    glGenBuffers(1, &normals_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
    glBufferData(GL_ARRAY_BUFFER, obj.normals.size() * sizeof(glm::vec3 ), &obj.normals[0], GL_STATIC_DRAW);

    GLuint uvs_vbo = 0;
    glGenBuffers(1, &uvs_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvs_vbo);
    glBufferData(GL_ARRAY_BUFFER, obj.uvs.size() * sizeof(glm::vec2 ), &obj.uvs[0], GL_STATIC_DRAW);


    glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer (GL_ARRAY_BUFFER, uvs_vbo);
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray (1);
    glEnableVertexAttribArray (2);

    //load texture and send it to the shader
    textureData.clear();
    if(loadTexture()){
        GLuint tex_vbo;
        glGenTextures(1, &tex_vbo);
        glBindTexture(GL_TEXTURE_2D, tex_vbo);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_FLOAT, &textureData[0]);
        //std::cout << "W" << textureWidth << "   H" << textureHeight <<"   "<<textureData.size() << std::endl;

        //tell the shader to use the texture
        glUniform1i(glGetUniformLocation(m_shader.programId(),"useTexture"), 1);
    }else{
        //tell the shader to use the user-defined colour
        glUniform1i(glGetUniformLocation(m_shader.programId(),"useTexture"), 0);
    }

    updateLights();
}

//translates the model
void GLWidget::translateModel(glm::vec3 translation){
    //set the translation matrix to the new translation
    translationMat = glm::translate(translationMat, translation);

    //push changed MVP to vertexShader
    updateMVP();
}

//rotate the model
void GLWidget::rotateModel(glm::vec3 rotationAxis, float degrees){
    //set the rotation matrix to the new rotation
    rotationMat = glm::rotate(rotationMat, degrees, rotationAxis);

    //push changed MVP matrix to vertexShader
    updateMVP();
}

//scales the model
void GLWidget::scaleModel(glm::vec3 scaleFactor){
    //set the scale matrix to the newly generated scale matrix
    scaleMat = glm::scale(scaleMat, scaleFactor);

    //push the changed MVP matrix to the vertex shader
    updateMVP();
}

//updates the MVP and pushes it to the vertex shader
void GLWidget::updateMVP(){
    //build up the modelMatrix from all the transformation matrices
    modelMat = translationMat * rotationMat * scaleMat;

    //build up the MVP matrix from the moedl, view and projection matrices
    glm::mat4 MVP = projection * view * modelMat;
    //push MVP matrix to the vertexShader
    glUniformMatrix4fv(glGetUniformLocation(m_shader.programId(),"MVP"), 1, GL_FALSE, &MVP[0][0]);

    glm::mat3 MVN = glm::inverseTranspose(glm::mat3(view * modelMat));
    glUniformMatrix3fv(glGetUniformLocation(m_shader.programId(),"MVN"), 1, GL_FALSE, &MVN[0][0]);

    //Redraw/update the scene
    updateLights();
    updateGL();
}

//rotates the lights by the number fo degrees specified.
void GLWidget::rotateLights(float degrees){
    //set the rotation matrix to the new rotation
    lightRotationMat = glm::rotate(lightRotationMat, degrees, glm::vec3(0.0f, 0.1f, 0.0f));

    //push changed lighting data to shader
    updateLights();
}

//update light vars and push them to the shader
void GLWidget::updateLights(){
    //computing position of rotated lights
    std::vector<float> rotatedLightPositions;
    for(int i = 0; i <  numLights; i++){
        //rotate about the origin then translate to where the model is so we always
        //rotate the lights around the model
        int offset = i * 3;
        glm::vec4 pos = glm::vec4(lightPositions[offset + 0], lightPositions[offset + 1], lightPositions[offset + 2], 1.0f);
        pos = translationMat * lightRotationMat * pos;

        rotatedLightPositions.push_back(pos[0]);
        rotatedLightPositions.push_back(pos[1]);
        rotatedLightPositions.push_back(pos[2]);
    }

    //send the updated light variables to the shader
    glUniform3fv(glGetUniformLocation(m_shader.programId(), "light_positions"), numLights, &rotatedLightPositions[0]);
    glUniform3fv(glGetUniformLocation(m_shader.programId(), "light_intensities"), numLights, &lightIntensities[0]);
    glUniform1fv(glGetUniformLocation(m_shader.programId(), "k_ambient"), 1, &k_ambient);
    updateGL();
}

//increments the ActiveAxis for transformations (cycles in range from 0 to 2)
void GLWidget::incrementActiveAxis(){
    activeAxis++;
    if(activeAxis > 2){
        activeAxis = 0;
    }
}

//Changes the render colour to one of 5 preset options
//NOTE: this colour will only be used if there is no texture on the object
void GLWidget::setRenderColor(int opt){
    switch(opt){
        case 1:
            //red
            red = 1.0f;
            blue = green = 0.0f;
            break;

        case 2:
            //green
            green = 1.0f;
            blue = red = 0.0f;
            break;

        case 3:
            //blue
            blue = 1.0f;
            red = green = 0.0f;
            break;

        case 4:
            //yellow
            red = green = 1.0f;
            blue = 0.0f;
            break;
        case 5:
            //white
            red = blue = green = 1.0f;
            break;

        default:
            //white
            setRenderColor(5);
    }

    //push new colour to fcolour uniform variable in the shader program
    glUniform4f(glGetUniformLocation(m_shader.programId(),"frag_colour"), red, green, blue, 1.0f);
    updateGL();
}

//Uses a file dialog to load a texture. The texture is then read in to the textureData vector.
bool GLWidget::loadTexture(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "~", tr("Image Files (*.png)"));
    QImage img;

    if (!fileName.isEmpty())
    {
        img = QImage(fileName, "PNG");
        textureWidth = img.width();
        textureHeight = img.height();

        for ( int row = 0; row < img.height(); ++row ){
            for ( int col = 0; col < img.width(); ++col )
            {
                QColor clrCurrent( img.pixel( col,row ) );
                textureData.push_back(clrCurrent.red()/255.0f);
                textureData.push_back(clrCurrent.green()/255.0f);
                textureData.push_back(clrCurrent.blue()/255.0f);
            }
        }
        return true; //texture was loaded
    }
    return false; //no texture was loaded
}



//GL-Functions----------------------------------------------------------------------------------------------------

//Loads neccessary components and sets up the OpenGl context
//Also loads and draws the model
void GLWidget::initializeGL(){
    // Resolve OpenGL functions
    glewExperimental = true;
    GLenum GlewInitResult = glewInit();
    if (GlewInitResult != GLEW_OK) {
        const GLubyte* errorStr = glewGetErrorString(GlewInitResult);
        size_t size = strlen(reinterpret_cast<const char*>(errorStr));
        qDebug() << "Glew error "
                 << QString::fromUtf8(
                        reinterpret_cast<const char*>(errorStr), size);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable (GL_CULL_FACE); // cull face
    glCullFace (GL_BACK); // cull back face
    glFrontFace (GL_CCW); // GL_CCW for counter clock-wise

    glEnable(GL_TEXTURE_2D);

    // get context opengl-version
    qDebug() << "Widget OpenGl: " << format().majorVersion() << "." << format().minorVersion();
    qDebug() << "Context valid: " << context()->isValid();
    qDebug() << "Really used OpenGl: " << context()->format().majorVersion() << "." << context()->format().minorVersion();
    qDebug() << "OpenGl information: VENDOR:       " << (const char*)glGetString(GL_VENDOR);
    qDebug() << "                    RENDERDER:    " << (const char*)glGetString(GL_RENDERER);
    qDebug() << "                    VERSION:      " << (const char*)glGetString(GL_VERSION);
    qDebug() << "                    GLSL VERSION: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

    QGLFormat glFormat = QGLWidget::format();
    if ( !glFormat.sampleBuffers() )
        qWarning() << "Could not enable sample buffers";

    // Set the clear color to black
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );


    //If we have a model to load, then load it
    if(model_filename != ""){
        loadModel();
    }


    //set up the projection matrix (perspective projection for our 3d models)
    projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 10.0f);

    //set up the view matrix (the "camera")
    glm::vec3 eye(0, 0, 3);
    glm::vec3 center(0, 0, 0);
    glm::vec3 up(0, 1, 0);
    view = glm::lookAt(eye, center, up);

    //set up the model matrices (initialise all transformation matrices to id matrix)
    translationMat = glm::mat4(1.0f);
    rotationMat = glm::mat4(1.0f);
    scaleMat = glm::mat4(1.0f);

    //create MVP matrix ad push it to the vertex shader
    updateMVP();
}

void GLWidget::resizeGL( int w, int h )
{
    // Set the viewport to window dimensions
    glViewport( 0, 0, w, qMax( h, 1 ) );
}

void GLWidget::paintGL()
{
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    // Clear the buffer with the current clearing color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Draw stuff
    glDrawArrays( GL_TRIANGLES, 0,  obj.vertices.size());
}

bool GLWidget::prepareShaderProgram( const QString& vertexShaderPath,
                                     const QString& fragmentShaderPath )
{
    // First we load and compile the vertex shader...
    bool result = m_shader.addShaderFromSourceFile( QOpenGLShader::Vertex, vertexShaderPath );
    if ( !result )
        qWarning() << m_shader.log();

    // ...now the fragment shader...
    result = m_shader.addShaderFromSourceFile( QOpenGLShader::Fragment, fragmentShaderPath );
    if ( !result )
        qWarning() << m_shader.log();

    // ...and finally we link them to resolve any references.
    result = m_shader.link();
    if ( !result )
        qWarning() << "Could not link shader program:" << m_shader.log();

    return result;
}
