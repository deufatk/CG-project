#include <GL/freeglut.h>
#include <cmath>
#include <vector>

const double PI = 3.141592653589793;

struct Planet {
    double distance; // Distance from the central star
    double angle;    // Angular position of the planet
    double speed;    // Speed of rotation
    double radius;   // Radius of the planet
    float color[3];  // RGB color of the planet
};

struct Orbit {
    double distance; // Distance from the central star
};

struct StarSystem {
    std::vector<Orbit> orbits;
    std::vector<Planet> planets;
    double rotationAngle; // Rotation angle of the entire star system
};

StarSystem starSystem;
double starSystemRotationSpeed = 0.05;

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);  // Enable color tracking for materials
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

    GLfloat light_position[] = {1.0f, 1.0f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Adjusted material properties for a more realistic look
    GLfloat material_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat material_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f}; // White
    GLfloat material_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat material_shininess = 50.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);
}

void drawSphere(double radius) {
    glutSolidSphere(radius, 50, 50);
}

void drawOrbit(double distance) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        double angle = i * PI / 180.0;
        glVertex3d(distance * cos(angle), 0.0, distance * sin(angle));
    }
    glEnd();
}

void drawStarSystem() {
    glPushMatrix();
    glRotated(starSystem.rotationAngle, 0.0, 1.0, 0.0); // Rotate the entire star system

    // Draw orbits
    glColor3f(0.5f, 0.5f, 0.5f); // Set a color for orbits
    for (size_t i = 0; i < starSystem.orbits.size(); ++i) {
        glPushMatrix();
        drawOrbit(starSystem.orbits[i].distance);
        glPopMatrix();
    }

    // Draw central star (Sun)
    glDisable(GL_LIGHTING);  // Disable lighting for the Sun
    glColor3f(1.0f, 0.8392f, 0.6118f); // Sun-like color
    drawSphere(1.0);
    glEnable(GL_LIGHTING);  // Enable lighting again

    // Draw planets
    for (size_t i = 0; i < starSystem.planets.size(); ++i) {
        glPushMatrix();
        glRotated(starSystem.planets[i].angle * 180.0 / PI, 0.0, 1.0, 0.0);
        glTranslated(starSystem.planets[i].distance * cos(starSystem.planets[i].angle),
                     0.0,
                     starSystem.planets[i].distance * sin(starSystem.planets[i].angle));

        // Set color based on the planet
        glColor3fv(starSystem.planets[i].color);
        drawSphere(starSystem.planets[i].radius);

        glPopMatrix();
    }

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Adjusted viewpoint

    drawStarSystem();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(w) / h, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle() {
    starSystem.rotationAngle += starSystemRotationSpeed;
    for (size_t i = 0; i < starSystem.planets.size(); ++i) {
        starSystem.planets[i].angle += starSystem.planets[i].speed;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Planet Simulation");

    init();

    // Initialize orbits and planets in the star system
    Orbit orbit1 = {2.0};
    Orbit orbit2 = {4.0};
    Orbit orbit3 = {6.0};
    Orbit orbit4 = {8.0};
    Orbit orbit5 = {10.0};
    Orbit orbit6 = {12.0};
    Orbit orbit7 = {14.0};
    Orbit orbit8 = {16.0};

    // Initialization of planets with manual speed values
    Planet mercury = {2.0, 0.0, 2.0, 0.1, {0.7f, 0.7f, 0.7f}};
    Planet venus = {4.0, PI / 4, 1.0, 0.15, {1.0f, 0.5f, 0.0f}};
    Planet earth = {6.0, PI / 2, 0.67, 0.2, {0.0f, 0.0f, 1.0f}};
    Planet mars = {8.0, PI / 3, 0.5, 0.18, {1.0f, 0.0f, 0.0f}};
    Planet jupiter = {10.0, PI / 6, 0.25, 0.4, {0.8f, 0.6f, 0.4f}};
    Planet saturn = {12.0, PI / 8, 0.2, 0.35, {0.9f, 0.9f, 0.5f}};
    Planet uranus = {14.0, PI / 10, 0.15, 0.3, {0.5f, 0.8f, 0.8f}};
    Planet neptune = {16.0, PI / 12, 0.125, 0.25, {0.0f, 0.0f, 0.5f}};

    starSystem.orbits.push_back(orbit1);
    starSystem.orbits.push_back(orbit2);
    starSystem.orbits.push_back(orbit3);
    starSystem.orbits.push_back(orbit4);
    starSystem.orbits.push_back(orbit5);
    starSystem.orbits.push_back(orbit6);
    starSystem.orbits.push_back(orbit7);
    starSystem.orbits.push_back(orbit8);

    starSystem.planets.push_back(mercury);
    starSystem.planets.push_back(venus);
    starSystem.planets.push_back(earth);
    starSystem.planets.push_back(mars);
    starSystem.planets.push_back(jupiter);
    starSystem.planets.push_back(saturn);
    starSystem.planets.push_back(uranus);
    starSystem.planets.push_back(neptune);


    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
