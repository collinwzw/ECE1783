#include "YUVVideo.h"
#include "RGBVideo.h"

class Converter{
    public:
        Converter(){}
        void YUV444ToRGB(YUVVideo YUV444Video,RGBVideo rgbvideo ){
            float cof[3][3] = {{1.164,0,1.596},{1.164,-0.392,-0.813},{1.164,2.017,0}};
            uint8_t OFFSET_Y = -16;
            uint8_t OFFSET_U = -128;
            uint8_t OFFSET_V = -128;

            for (int i = 0; i < YUV444Video.frameNumber; i++){
                //read data for Y plane
                for (int row =0; row < YUV444Video.getFrame(i).Y.numberOfRow; row++){
                    for (int col =0; col < YUV444Video.getFrame(i).Y.numberOfColumn; col++){
                        uint8_t Y = YUV444Video.getFrame(i).Y.getData(row,col) + OFFSET_Y;
                        uint8_t U = YUV444Video.getFrame(i).U.getData(row,col) + OFFSET_U;
                        uint8_t V = YUV444Video.getFrame(i).V.getData(row,col) + OFFSET_V;

                        uint8_t R = Y*cof[0][0] + U*cof[0][1] + V*cof[0][2];
                        uint8_t G = Y*cof[1][0] + U*cof[1][1] + V*cof[1][2];
                        uint8_t B = Y*cof[2][0] + U*cof[2][1] + V*cof[2][2];
                        
                        rgbvideo.getFrame(i).R.setData(row,col,R);
                        rgbvideo.getFrame(i).G.setData(row,col,G);
                        rgbvideo.getFrame(i).B.setData(row,col,B);

                    }
                }            
            }
        }
};
