# -*- coding: utf-8 -*-
"""
Created on Fri May 16 13:18:17 2014

Reads in an image and averages the pixel values of R,G,B.

@author: Cameron Nouri
"""

from PIL import Image
import operator

# Assumes that skybox images always follow the same file format.
def readSkyboxImages(skybox_dir):
    skybox_path = "../data/textures/skyboxes/";

    # Check if there's a backslash on the end of the input folder. Remove it.
    if skybox_dir[-1] == '//':
        skybox_dir = skybox_dir[:-1]

    im_back = Image.open(skybox_path + skybox_dir + "/back.png");
    im_front = Image.open(skybox_path + skybox_dir + "/front.png");
    im_left = Image.open(skybox_path + skybox_dir + "/left.png");
    im_right = Image.open(skybox_path + skybox_dir + "/right.png");    
    im_up = Image.open(skybox_path + skybox_dir + "/up.png");    
    im_down = Image.open(skybox_path + skybox_dir + "/down.png");
    
    pix_back = im_back.load();
    pix_front = im_front.load();
    pix_left = im_left.load();
    pix_right = im_right.load();
    pix_up= im_up.load();
    pix_down = im_down.load();
    
    globalPixImg = Image.new('RGB', (1,1))
    final_pixel = globalPixImg.load() 
    pixel = (0, 0, 0)    
    
    for i in range(im_back.size[0]):
        for j in range(im_back.size[1]):
            pixel = tuple(map(operator.add, pixel, pix_back[i,j]))
            pixel = tuple(map(operator.add, pixel, pix_front[i,j]))
            pixel = tuple(map(operator.add, pixel, pix_left[i,j]))
            pixel = tuple(map(operator.add, pixel, pix_right[i,j]))
            pixel = tuple(map(operator.add, pixel, pix_up[i,j]))
            pixel = tuple(map(operator.add, pixel, pix_down[i,j]))  
        
    final_norm = im_back.size[0] * im_back.size[1] * 6
    final_pixel[0,0] = (pixel[0]/final_norm, pixel[1]/final_norm, pixel[2]/final_norm)
    
    globalPixImg.save(skybox_path + skybox_dir + "/global.png","PNG")
    
if __name__ == '__main__':
    skybox_dir = raw_input('Input skybox folder name\n');
    #print skybox_dir;
    readSkyboxImages(skybox_dir)

#im = Image.open("data/textures/skyboxes/crater");
#im.rotate(45).show()