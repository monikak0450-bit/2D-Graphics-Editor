#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 24

#define EMPTY '_'
#define PIXEL '*'

char picture[HEIGHT][WIDTH];
typedef struct {
    int type;
    int data[6];
    int active;
} Shape;

Shape shapes[100];
int shapeCount = 0;

void clearPicture() {
    /*
        TODO:
        Fill the entire 2D array picture with EMPTY character '_'.
    */
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            picture[y][x] = EMPTY;
        }
    }
}

void displayPicture() {
    /*
        TODO:
        Print the 2D picture array row by row.
    */
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", picture[y][x]);
        }
        printf("\n");
    }
}

void setPixel(int x, int y) {
    /*
        TODO:
        If x and y are inside the canvas,
        set picture[y][x] to PIXEL character '*'.
    */
    if (x >= 0 && x < WIDTH &&
        y >= 0 && y < HEIGHT) {
        picture[y][x] = PIXEL;
    }
}

void drawLine(int x1, int y1, int x2, int y2) {
    /*
        TODO:
        Draw a line from (x1, y1) to (x2, y2)
        using the '*' character.
    */
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (1) {
        setPixel(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


void drawRectangle(int x1, int y1, int x2, int y2) {
    /*
        TODO:
        Draw a rectangle using four lines.
        Top-left corner is (x1, y1).
        Bottom-right corner is (x2, y2).
    */
    drawLine(x1, y1, x2, y1); // Top
    drawLine(x2, y1, x2, y2); // Right
    drawLine(x2, y2, x1, y2); // Bottom
    drawLine(x1, y2, x1, y1); // Left
}

void drawCircle(int cx, int cy, int radius) {
    /*
        TODO:
        Draw a circle with center (cx, cy)
        and given radius using '*'.
    */
    int x = radius;
    int y = 0;
    int decision = 1 - radius;

    while (x >= y) {
        setPixel(cx + x, cy + y);
        setPixel(cx + y, cy + x);
        setPixel(cx - y, cy + x);
        setPixel(cx - x, cy + y);
        setPixel(cx - x, cy - y);
        setPixel(cx - y, cy - x);
        setPixel(cx + y, cy - x);
        setPixel(cx + x, cy - y);

        y++;

        if (decision <= 0) {
            decision += 2 * y + 1;
        } else {
            x--;
            decision += 2 * (y - x) + 1;
        }
    }
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    /*
        TODO:
        Draw a triangle by joining the three given points.
    */
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}
void listShapes();
void deleteShape(int id);

void listShapes()
{
    for(int i = 0; i < shapeCount; i++)
    {
        if(shapes[i].active)
        {
            printf("ID %d Type %d\n", i, shapes[i].type);
        }
    }
}

void deleteShape(int id)
{
    if(id >= 0 && id < shapeCount)
    {
        shapes[id].active = 0;
    }
}
int main() {
    int choice;

    clearPicture();

    printf("2D Graphics Editor\n");
    printf("Canvas size: %d x %d\n", WIDTH, HEIGHT);
    printf("Use coordinates x y.\n");
    printf("x range: 0 to %d\n", WIDTH - 1);
    printf("y range: 0 to %d\n", HEIGHT - 1);

    while (1) {
        printf("\nMenu\n");
        printf("1. Draw Line\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Circle\n");
        printf("4. Draw Triangle\n");
        printf("5. Display Picture\n");
        printf("6. List Objects\n");
        printf("7. Delete Object\n");
        printf("8. Modify Object\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        if (choice == 1) {
            int x1, y1, x2, y2;

            printf("Enter x1 y1 x2 y2: ");
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

            drawLine(x1, y1, x2, y2);
            shapes[shapeCount].type = 1;

shapes[shapeCount].data[0] = x1;
shapes[shapeCount].data[1] = y1;
shapes[shapeCount].data[2] = x2;
shapes[shapeCount].data[3] = y2;

shapes[shapeCount].active = 1;

shapeCount++;
        }
        else if (choice == 2) {
            int x1, y1, x2, y2;

            printf("Enter top-left x y and bottom-right x y: ");
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

            drawRectangle(x1, y1, x2, y2);
            shapes[shapeCount].type = 2;

            shapes[shapeCount].data[0] = x1;
            shapes[shapeCount].data[1] = y1;
            shapes[shapeCount].data[2] = x2;
            shapes[shapeCount].data[3] = y2;

            shapes[shapeCount].active = 1;

            shapeCount++;
        }
        else if (choice == 3) {
            int cx, cy, radius;

            printf("Enter center x y and radius: ");
            scanf("%d %d %d", &cx, &cy, &radius);

            drawCircle(cx, cy, radius);
            shapes[shapeCount].type = 3;

            shapes[shapeCount].data[0] = cx;
            shapes[shapeCount].data[1] = cy;
            shapes[shapeCount].data[2] = radius;

            shapes[shapeCount].active = 1;

            shapeCount++;
        }
        else if (choice == 4) {
            int x1, y1, x2, y2, x3, y3;

            printf("Enter x1 y1 x2 y2 x3 y3: ");
            scanf("%d %d %d %d %d %d",
                  &x1, &y1, &x2, &y2, &x3, &y3);

            drawTriangle(x1, y1, x2, y2, x3, y3);
            shapes[shapeCount].type = 4;

shapes[shapeCount].data[0] = x1;
shapes[shapeCount].data[1] = y1;
shapes[shapeCount].data[2] = x2;
shapes[shapeCount].data[3] = y2;
shapes[shapeCount].data[4] = x3;
shapes[shapeCount].data[5] = y3;

shapes[shapeCount].active = 1;

shapeCount++;
        }
        else if (choice == 5) {
            printf("The picture is:\n");
            displayPicture();
        }
        else if (choice == 6) {
            listShapes();
        }
else if (choice == 7) {
    int id;

    printf("Enter object ID to delete: ");
    scanf("%d", &id);

    deleteShape(id);
}
else if (choice == 8) {
    int id;

    printf("Enter object ID: ");
    scanf("%d", &id);

    if(id >= 0 && id < shapeCount && shapes[id].active)
    {
        if(shapes[id].type == 2)   // rectangle
        {
            printf("Enter new x1 y1 x2 y2: ");

            scanf("%d %d %d %d",
                  &shapes[id].data[0],
                  &shapes[id].data[1],
                  &shapes[id].data[2],
                  &shapes[id].data[3]);
        }
    }
}
        else if (choice == 0) {
            printf("Exiting program.\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}