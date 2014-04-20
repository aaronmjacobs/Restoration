virtual bool checkCollision(PhysicalObjectRef physObj) {
   //check if objects are on screen via clipping and culling
   if (this.xMax < physObj.xMin || this.xMin > physObj.xMax)
      return 0;
   if (this.yMax < physObj.yMin || this.yMin > physObj.yMax)
      return 0;
   return 1;
}