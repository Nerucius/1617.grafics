#include <math.h>
#include <GLWidget.h>
#include <QtDebug>
#include <QString>

char* gouraudVertPath = "../Practica2_Base-master/resources/gouraudVert.glsl";
char* gouraudFragPath = "../Practica2_Base-master/resources/gouraudFrag.glsl";

char* phongVertPath = "../Practica2_Base-master/resources/phongVert.glsl";
char* phongFragPath = "../Practica2_Base-master/resources/phongFrag.glsl";

char* phongTexVertPath = "../Practica2_Base-master/resources/phongTexVert.glsl";
char* phongTexFragPath = "../Practica2_Base-master/resources/phongTexFrag.glsl";

char* toonVertPath = "../Practica2_Base-master/resources/toonVert.glsl";
char* toongFragPath = "../Practica2_Base-master/resources/toonFrag.glsl";

GLWidget::GLWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {
    setFocusPolicy( Qt::StrongFocus );
    scene = new Scene();
    camera = new Camera();
}

GLWidget::~GLWidget() {
    makeCurrent();
    delete scene;
}

// Metodes que es criden des dels menús

void GLWidget::activaToonShader() {
    initShader(toonVertPath, toongFragPath);
    updateGL();
    cout<<"Estic a Toon"<<endl;
}

void GLWidget::activaPhongShader() {
    initShader(phongVertPath, phongFragPath);
    updateGL();
    cout<<"Estic a Phong"<<endl;

}

void GLWidget::activaGouraudShader() {
    initShader(gouraudVertPath, gouraudFragPath);
    updateGL();
    cout<<"Estic a Gouraud"<<endl;

}

void GLWidget::activaPhongTex() {
    initShader(phongTexVertPath, phongTexFragPath);
    updateGL();
    cout<<"Estic a Phong Tex"<<endl;
}

void GLWidget::activaGouraudTex() {
    // SKIPPED
}


void GLWidget::ensenyaMenuLight0() {
    // Agafa la darrera llum creada. A CANVIAR si es vol tenir control de totes les llums.
    // De fet el metode showAuxWindowPuntualLight té com a parametre la llum a mostrar en el widget.
    // Es podria cridar diverses vegades.
    if (scene->lights.size()>0)
        showAuxWindowPuntualLight(scene->getLightActual());
}

// Per a les llums: com afegir-les
void GLWidget::changePositionLight() {
    // TO DO: cal modificar en la fase 1 de la practica 2
    // Des d'quest mètode s'AFEGEIX una nova llum
    // tipus rep el tipus de llum que es vol afegir. Des d'aqui s'afegeix la llum a l'escena
    scene->getLightActual()->setTipusLight(Puntual);

}
void GLWidget::changeDirectionalLight() {
    // tipus rep el tipus de llum que es vol afegir. Des d'aqui s'afegeix la llum a l'escena.
    // TO DO: cal modificar en la fase 1 de la practica 2
    // Des d'quest mètode s'AFEGEIX una nova llum
    scene->getLightActual()->setTipusLight(Direccional);

}
void GLWidget::changeSpotLight() {
    // tipus rep el tipus de llum que es vol afegir. Des d'aqui s'afegeix la llum a l'escena.
    // TO DO: cal modificar en la fase 1 de la practica 2
    // Des d'quest mètode s'AFEGEIX una nova llum
    scene->getLightActual()->setTipusLight(Spot);

}
void GLWidget::updateXPositionLight(int xposition) {
    // S'ha de modificar la posicio x de la llum activa
    vec4 v = scene->getLightActual()->getPosition();
    v[0] = (float)xposition;
    scene->getLightActual()->setPosition(v);
}

void GLWidget::updateYPositionLight(int yposition) {
    // S'ha de modificar la posicio y de la llum activa
    vec4 v = scene->getLightActual()->getPosition();
    v[1] = (float)yposition;
    scene->getLightActual()->setPosition(v);
}

void GLWidget::updateZPositionLight(int zposition) {
    // S'ha de modificar la posicio z de la llum activa
    vec4 v = scene->getLightActual()->getPosition();
    v[2] = (float)zposition;
    scene->getLightActual()->setPosition(v);
}

void GLWidget::updateLightIntensity(int intens) {
    // S'ha de modificar la intensitat de la llum 0. es podria canviar per la llum actual
    vec3 intensitat;
    intensitat =  scene->getLightActual()->getId();
    intensitat[0] = intens/200.0;
    intensitat[1] = intens/200.0;
    intensitat[2] = intens/200.0; // el 200 es l'escala del scrollbar

    scene->getLightActual()->setId(intensitat);
}

void GLWidget::activateLight(){
    scene->getLightActual()->switchOnOff();
}

/** Toggle Normal Maps */
void GLWidget::activaBumpMapping() {

    int enBump;

    for (int i = 0; i < this->scene->elements.size(); i++){
        Object* o = this->scene->elements.at(i);
        enBump = o->enTexture[TexSlot::Normal] == 1 ? 0:1;

        o->enTexture[TexSlot::Normal] = enBump;
        o->toGPUTexture(this->program);
    }


    cout << "Normal maps: " << enBump << endl;
}

/** Toggle Emissive Night Map */
void GLWidget::activaEmissiveMap() {

    int enEmissive;

    for (uint i = 0; i < this->scene->elements.size(); i++){
        Object* o = this->scene->elements.at(i);
        enEmissive = o->enTexture[TexSlot::Emissive] == 1 ? 0:1;

        o->enTexture[TexSlot::Emissive] = enEmissive;
        o->toGPUTexture(this->program);
    }


    cout << "Emissive maps: " << enEmissive << endl;
}

void GLWidget::activaEnvMapping() {
    //To DO: a implementar a la fase 2 de la practica 2
}


// Mètodes d'interacció amb el ratolí

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    std::cout<<"Press button"<<std::endl;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = -(event->x() - lastPos.x());
    int dy = -(event->y() - lastPos.y());

        std::cout<<"M button"<<std::endl;
    if (event->buttons() & Qt::LeftButton)
    {
        if(lastPos.y()!= event->y() && lastPos.x()!= event->x()) {
           setXRotation(dy);
           setYRotation(dx);
        } else if(lastPos.y()!= event->y()) {// rotar la camera
            setXRotation(dy);
        } else if (lastPos.x()!= event->x()) {
            setYRotation(dx);
        }

    } else if (event->buttons() & Qt::RightButton) {
       // Zoom: canviar la mida de la window
        if(lastPos.y()> event->y())
             Zoom(-1);
        else
             Zoom(1);
    }

    lastPos = event->pos();
}


void GLWidget::setXRotation(int angle)
{
    if (angle >0) {
        camera->angX += 5;
    } else if (angle<0)
        camera->angX -= 5;
    qNormalizeAngle(camera->angX);

    camera->rotaCamera(scene->capsaMinima);
    updateGL();
}

void GLWidget::setYRotation(int angle)
{
    if (angle >0) {
        camera->angY += 5;
    } else if (angle<0)
        camera->angY-= 5;
    qNormalizeAngle(camera->angY);

    camera->rotaCamera(scene->capsaMinima);
    updateGL();

}

void GLWidget::qNormalizeAngle(double &angle)
{
    while (angle < 0)
        angle += 360*16;
    while (angle > 360)
        angle -= 360*16;
}

void GLWidget::Zoom (int positiu) {
    camera->AmpliaWindow(positiu*(0.005));

    updateGL();

}

void GLWidget::initShader(const char* vShaderFile, const char* fShaderFile){
    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);
    program->link();
    program->bind();

    for (int i = 0; i < this->scene->elements.size(); i++){
        Object* o = this->scene->elements.at(i);
        o->toGPUTexture(this->program);
    }
}

/**
 * @brief GLWidget::initShadersGPU
 */
void GLWidget::initShadersGPU(){
    initShader(phongTexVertPath, phongTexFragPath);
}

QSize GLWidget::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const {
    return QSize(400, 400);
}

void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_RGBA);
    glEnable(GL_DOUBLE);

    initShadersGPU();

    // Creacio d'una Light per apoder modificar el seus valors amb la interficie
//    Light *l = new Light(Puntual);
//    scene->addLight(l);

    camera->init(this->size().width(), this->size().height(), scene->capsaMinima);
    glViewport(camera->vp.pmin[0], camera->vp.pmin[1], camera->vp.a, camera->vp.h);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/** Render method for the OpenGL window */
void GLWidget::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable(GL_ALPHA);
    glAlphaFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set camera matrices on shader
    camera->toGPU(program);

    // Send lights to GPU
    scene->ambientToGPU(program);
    scene->lightsToGPU(program);

    // Draw SCENE
    scene->drawTexture();
}


void GLWidget::resizeGL(int width, int height) {
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    camera->vp.pmin[0] = (width - side) / 2;
    camera->vp.pmin[1] = (height - side) / 2;
    camera->vp.a = side;
    camera->vp.h = side;
    updateGL();
}

void GLWidget::newObj(QString path){
    qDebug() << path;


    // Earth Sphere Best Parameters

    Material* mat = new Material( vec3(.1), vec3(.6), vec3(.3), 4);
    Object * obj = new Object(100000, path, mat);

    obj->initTextura("../Practica2_Base-master/resources/textures/earth1.png", TexSlot::Diffuse);
    obj->initTextura("../Practica2_Base-master/resources/textures/2k_earth_specular_map.jpg", TexSlot::Specular);
    obj->initTextura("../Practica2_Base-master/resources/textures/earth3.png", TexSlot::Normal);
    obj->initTextura("../Practica2_Base-master/resources/textures/earth2.png", TexSlot::Emissive);
    obj->enTexture[TexSlot::Normal] = 0;

    // Red Teapot Best Parameters
    /*
    Material* mat = new Material( vec3(.4,0,0), vec3(.8,.1,.1), vec3(0,.6,0), 4);
    Object * obj = new Object(100000, path, mat);
    */


    obj->toGPUTexture(program);
    scene->addObject(obj);
    camera->actualitzaCamera(scene->capsaMinima);
    updateGL();
}

// Finestra per a introduir una Light puntual o modificar-ne el seu contingut
void GLWidget::showAuxWindowPuntualLight(Light *light)
{
    auxWidget = new QWidget;
    auxWidget->move(0,0);

    QVBoxLayout *outer = new QVBoxLayout;
    QHBoxLayout *buttons = new QHBoxLayout;

    QGroupBox *groupBox = new QGroupBox("Light type");
    QRadioButton *radio1 = new QRadioButton("Position light");
    connect(radio1, SIGNAL(clicked()), this, SLOT(changePositionLight()));
    radio1->setChecked(true);

    QRadioButton *radio2 = new QRadioButton("Directional light");
    connect(radio2, SIGNAL(clicked()), this, SLOT(changeDirectionalLight()));
    radio2->setChecked(false); // Quan es clica es modifica el tipus de Light

    QRadioButton *radio3 = new QRadioButton("Spot light");
    connect(radio3, SIGNAL(clicked()), this, SLOT(changeSpotLight()));
    radio3->setChecked(false); // Sols quan es clica es modifica el tipus de  Light

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);

    groupBox->setLayout(vbox);
    buttons->addWidget(groupBox);

    QGroupBox *groupBox2 = new QGroupBox("Selection");

    QRadioButton *transparent1 = new QRadioButton("&On");
    transparent1->setChecked(true);
    connect(transparent1, SIGNAL(clicked()), this, SLOT(activateLight()));

    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(transparent1);

    groupBox2->setLayout(vbox2);
    buttons->addWidget(groupBox2);
    outer->addLayout(buttons);

    // light source intensity
    QSlider* lightSlider = new QSlider(Qt::Horizontal);
    lightSlider->setTickPosition(QSlider::TicksBelow);
    lightSlider->setMinimum(0);
    lightSlider->setMaximum(200);
    if (light == NULL)
        lightSlider->setSliderPosition(100);
    else
        lightSlider->setSliderPosition(100*light->getId()[0]);
    connect(lightSlider,SIGNAL(valueChanged(int)),this,SLOT(updateLightIntensity(int)));
    QLabel* lightLabel = new QLabel("Light intensity = ");
    QLabel* lightLabelValue = new QLabel();
    lightLabelValue->setNum(100 * light->getId()[0]);
    connect(lightSlider,SIGNAL(valueChanged(int)),lightLabelValue,SLOT(setNum(int)));
    QHBoxLayout *hboxLight = new QHBoxLayout;
    hboxLight->addWidget(lightLabel);
    hboxLight->addWidget(lightLabelValue);
    outer->addLayout(hboxLight);
    outer->addWidget(lightSlider);

    // X slider
    QSlider* XSlider = new QSlider(Qt::Horizontal);
    XSlider->setTickPosition(QSlider::TicksBelow);
    XSlider->setMinimum(-100);
    XSlider->setMaximum(100);
    if (light == NULL)
        XSlider->setSliderPosition(100);
    else
        XSlider->setSliderPosition(light->getPosition()[0]);
    connect(XSlider,SIGNAL(valueChanged(int)),this,SLOT(updateXPositionLight(int)));
    QLabel* XLabel = new QLabel("X Position = ");
    QLabel* XLabelValue = new QLabel();
    XLabelValue->setNum(0);
    connect(XSlider,SIGNAL(valueChanged(int)),XLabelValue,SLOT(setNum(int)));
    QHBoxLayout *hboxX = new QHBoxLayout;
    hboxX->addWidget(XLabel);
    hboxX->addWidget(XLabelValue);
    outer->addLayout(hboxX);
    outer->addWidget(XSlider);

    // Y slider
    QSlider* YSlider = new QSlider(Qt::Horizontal);
    YSlider->setTickPosition(QSlider::TicksBelow);
    YSlider->setMinimum(-100);
    YSlider->setMaximum(100);
    if (light == NULL)
        YSlider->setSliderPosition(100);
    else
        YSlider->setSliderPosition(light->getPosition()[1]);

    connect(YSlider,SIGNAL(valueChanged(int)),this,SLOT(updateYPositionLight(int)));
    QLabel* YLabel = new QLabel("Y Position = ");
    QLabel* YLabelValue = new QLabel();
    YLabelValue->setNum(0);
    connect(YSlider,SIGNAL(valueChanged(int)),YLabelValue,SLOT(setNum(int)));
    QHBoxLayout *hboxY = new QHBoxLayout;
    hboxY->addWidget(YLabel);
    hboxY->addWidget(YLabelValue);
    outer->addLayout(hboxY);
    outer->addWidget(YSlider);

    // Z Slider
    QSlider* ZSlider = new QSlider(Qt::Horizontal);
    ZSlider->setTickPosition(QSlider::TicksBelow);
    ZSlider->setMinimum(-100);
    ZSlider->setMaximum(100);
    if (light == NULL)
        ZSlider->setSliderPosition(100);
    else
        ZSlider->setSliderPosition(light->getPosition()[2]);
    connect(ZSlider,SIGNAL(valueChanged(int)),this,SLOT(updateZPositionLight(int)));
    QLabel* ZLabel = new QLabel("Z Position = ");
    QLabel* ZLabelValue = new QLabel();
    ZLabelValue->setNum(0);
    connect(ZSlider,SIGNAL(valueChanged(int)),ZLabelValue,SLOT(setNum(int)));
    QHBoxLayout *hboxZ = new QHBoxLayout;
    hboxZ->addWidget(ZLabel);
    hboxZ->addWidget(ZLabelValue);
    outer->addLayout(hboxZ);
    outer->addWidget(ZSlider);

    // Es poden afegir més camps a explorar amb el widget
    // Afegiu-los aqui sota

    auxWidget->setLayout(outer);
    auxWidget->show();
}

