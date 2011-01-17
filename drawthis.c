int i;
float center_x = 300;
float center_y = 300;
//draw_brush(widget, center_x, center_y);
float radius = 100;
float line_y = center_y+90;

for(i = 0; i < 800; i++) { //for all values of x
float xval = sqrt((radius*radius)-((i-center_x)*(i-center_y))); //bottom
float otherxval = 0-sqrt((radius*radius)-((i-center_x)*(i-center_y)));

if(i < center_x-radius) {
draw_brush(widget, i, line_y);
}
if((xval+center_y < line_y)&&(i < center_x)) {
draw_brush(widget, i, line_y);
}
if((xval+center_y < line_y)&&(i < center_x)) {
draw_brush(widget, i, xval+center_y);
}
if (otherxval+center_y < line_y){
draw_brush(widget, i, otherxval+center_y);
}
//if (otherxval+center_y < line_y){
//draw_brush(widget, i, otherxval+center_y);
//}
if((xval+center_y < line_y)&&(i > center_x)) {
draw_brush(widget, i, xval+center_y);
}
if((xval+center_y < line_y)&&(i > center_x)) {
draw_brush(widget, i, line_y);
}
if(i > center_x+radius) {
draw_brush(widget, i, line_y);
}
}