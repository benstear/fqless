#include "DNA.h"


DNA::DNA(){

}

void DNA::append(string& sDNA){
	base b;
	for(auto it = sDNA.begin(); it != sDNA.end(); ++it) {
		b = char2DNA(*it);
		sequence.push_back(b);
	}
}

void DNA::addQuality(string& qal){
	uint q;
	uint i = 0;
	for(auto it = qal.begin(); it != qal.end(); ++it) {
		q = static_cast<uint>(*it);
		
		if( i < sequence.size()){
            sequence[i].quality = q;
        }
		i++;
	}
}

/*
string DNA::getSequence(){
	string DNAstring;
	uint i = 0;
	
	for(auto it = sequence.begin(); it != sequence.end(); it++){
		DNAstring[i] = DNA2char(*it);
		i++;
	}	

	return DNAstring;
}
*/



base DNA::char2DNA(char& dnaChar){
    base b;
    b.code = dnaChar;
    
	return b;
}

void DNA::printColoredDNA(WINDOW* win, std::pair<uint, uint> p){
    base b;
    char a;
    
    bool changeColor;
    changeColor = can_change_color();

	for(auto it = sequence.begin(); it != sequence.end(); ++it) {
		b = (*it);
		a = b.code;//DNA2char(b);
		
		if(changeColor){
		    //printw("yes");
		    color c;
		    c = IntToColor(b.quality, p);

		    init_color(b.quality, c.R,c.G,c.B);
		    init_pair(b.quality, b.quality, -1);
		    wattron(win, COLOR_PAIR(b.quality));
		    waddch(win, a);
            wattroff(win, COLOR_PAIR(b.quality));
		}else{
		    printw("no");
		}
	}
}



color DNA::IntToColor(int i, std::pair<uint, uint> p){
        // these are the maximal ASCII values used for quality scores
        // we can map everything into this range
        uint max;
        uint min;
        float range;
        max     = 126;
        min     = 33;
        range   = 41;
        
        min = p.first;
        max = p.second;
        range = max - min;
        
        // floor the number, so 0 is 0.
        float n;
        n       = i - min;
        n       /= range;
        max     = max - min;
        
       
        color result;
        float m  = 1;
        uint scale = 1000;
        result.R = floor(( (1 - n) * m ) * scale);
        result.G = floor(( n * m )* scale);
        result.B = 0;
        
        if(result.R > scale){ result.R = scale;}
        if(result.G > scale){ result.G = scale;}
        
        //cout << n << " " << result.R << " " << result.G << "- " ;
     
        return result;
    }
