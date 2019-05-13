#define ROW      60          //图像处理图像采集行数
#define COLUMN   160      // 图像处理图像采集点数  

#define H   CAMERA_H           //原始图像采集行数
#define V   CAMERA_W        // 原始图像采集点数 


/***************函数*******************/

void img_extract(uint8 *dst,uint8 *src,uint32 srclen);  //将DMA采集数据Pix_Data变成图像数据储存在image_pri数组内
void vsy_isr();  //中断函数接受dma请求，并处理图像
void image_select(uint8 *dst,uint8 *src);
