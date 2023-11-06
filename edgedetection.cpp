#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

 
#define IMAGE_HEIGHT 256
#define IMAGE_WIDTH 256
#define KERNEL_HEIGHT 3
#define KERNEL_WIDTH 3

void readFile(const char* inputName, unsigned char gray_matrix[][IMAGE_WIDTH]) {
    FILE* fptr = fopen(inputName, "rb");
    fread(gray_matrix, sizeof(unsigned char), IMAGE_WIDTH * IMAGE_HEIGHT, fptr);
    fclose(fptr);
}

void writeFile(const char* outputName, unsigned char edgedetection_matrix[][IMAGE_WIDTH]) {
    FILE* fptr = fopen(outputName, "wb");
    fwrite(edgedetection_matrix, sizeof(unsigned char), IMAGE_WIDTH * IMAGE_HEIGHT, fptr);
    fclose(fptr);
}

void convolution(unsigned char image[IMAGE_HEIGHT][IMAGE_WIDTH], int kernel[KERNEL_HEIGHT][KERNEL_WIDTH], unsigned char result[IMAGE_HEIGHT][IMAGE_WIDTH]) {
    int kCenterX = KERNEL_HEIGHT / 2;
    int kCenterY = KERNEL_WIDTH / 2;

    for (int i = 0; i < IMAGE_HEIGHT; ++i) {
        for (int j = 0; j < IMAGE_WIDTH; ++j) {
            int sum = 0;

            for (int m = 0; m < KERNEL_HEIGHT; ++m) {
                int mm = KERNEL_HEIGHT - 1 - m;
                for (int n = 0; n < KERNEL_WIDTH; ++n) {
                    int nn = KERNEL_WIDTH - 1 - n;
                    int ii = i + (kCenterY - mm);
                    int jj = j + (kCenterX - nn);

                    if (ii >= 0 && ii < IMAGE_HEIGHT && jj >= 0 && jj < IMAGE_WIDTH) {
                        sum += image[ii][jj] * kernel[mm][nn];
                    }
                }
            }

            result[i][j] = (unsigned char)sum;
        }
    }
}

void G_value(unsigned char matrixA[IMAGE_HEIGHT][IMAGE_WIDTH], unsigned char matrixB[IMAGE_HEIGHT][IMAGE_WIDTH], unsigned char result[IMAGE_HEIGHT][IMAGE_WIDTH]) {
    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        for (int j = 0; j < IMAGE_WIDTH; j++) {
            result[i][j] = sqrt((matrixA[i][j]^2 + matrixB[i][j]^2));
        }
    }
}



int main() {
    unsigned char image[IMAGE_HEIGHT][IMAGE_WIDTH];
    unsigned char result[IMAGE_HEIGHT][IMAGE_WIDTH];
    unsigned char result1[IMAGE_HEIGHT][IMAGE_WIDTH];
    unsigned char result2[IMAGE_HEIGHT][IMAGE_WIDTH]; 

    int kernel_x[KERNEL_HEIGHT][KERNEL_WIDTH] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int kernel_y[KERNEL_HEIGHT][KERNEL_WIDTH] = {
        {-1, -2, 1},
        {0, 0, 0},
        {1, 2, 1}
    };

    const char* inputName = "C:/Users/MY COMPUTER/Downloads/raw_gray.dat";
    const char* outputName = "C:/Users/MY COMPUTER/Downloads/edge_detection.dat";

    readFile(inputName, image);
    convolution(image, kernel_x, result1);
    convolution(image, kernel_y, result2);
    G_value(result1, result2, result);

    writeFile(outputName, result);

    return 0;
}
