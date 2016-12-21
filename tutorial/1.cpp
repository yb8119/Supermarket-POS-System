
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>

// SIMPLE WIDGET THAT DRAWS AN CHESS BOARD
class DrawCB : public Fl_Widget {
public:
    DrawCB(int X, int Y, int W, int H, const char*L=0) : Fl_Widget(X,Y,W,H,L) {
    }
    void draw() {
        // DRAW CHESS BOARD
		int lr = 8;
		int i,j;
		int x,y;
		for(i=0;i < lr;i++){
			for(j=0;j < lr;j++){
			x = 20*(i%lr);
			y=	20*(j%lr);
			if((i+j)%2){
				fl_draw_box(FL_FLAT_BOX,x,y,20,20,FL_RED);
			}
			else{
				fl_draw_box(FL_FLAT_BOX,x,y,20,20,FL_WHITE);
			}
			}
		}
    }
};
int main() {
    Fl_Double_Window win(200,200,"Draw The Chess Board");
    DrawCB draw_cb(0, 0, win.w(), win.h());
    win.resizable(draw_cb);
    win.show();
    return(Fl::run());
}