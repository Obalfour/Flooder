#include <gb/gb.h>
#include <gb/cgb.h> // Include cgb functions
#include <stdint.h>
#include <stdio.h>
#include <rand.h>
#include "utils.h"
#include "gbt_player.h"

extern const unsigned char * song_Data[];

void main(void)
{
	enum colorsMenu color_state = purple;
	enum colorsMenu prev_color;
	UINT8 board[14][14];
	UINT8 moves = 25;

	uint8_t joypad_current = 0x00u;
	uint8_t joypad_last = 0x00u;

	NR50_REG = 0xFF;
	NR51_REG = 0xFF;
	NR52_REG = 0x80;

	SHOW_BKG;
    DISPLAY_ON;

	SPRITES_8x8;

	disable_interrupts();

    gbt_play(song_Data, 1, 2);
    gbt_loop(0);

    set_interrupts(VBL_IFLAG);
    enable_interrupts();

	set_bkg_palette(0, 1, yourlogogb_palettes); // load palettes

	set_bkg_data(0, 103, yourlogogb_tiles); // load background tileset
	set_bkg_tiles(0, 0, 20, 18, yourlogogb_map);

	performantdelay(60);

	fadein();

	set_sprite_palette(0, 7, spritePalette); // load palettes
   	//set_win_data(75, 1, TILESET);
	//set_bkg_tiles(0, 0, 20, 18, TILEMAP);
	set_sprite_data(0, 13, sprite);

	transition2();

	set_bkg_data(0, 119, TILESET); // load background tileset
	//onlyCGB(); 

	set_bkg_palette(0, 1, bw_palettes); // load palettes

	// switch to 2nd video memory bank
	VBK_REG = 1;

	// set background color palette map, do this first
	set_bkg_tiles(0, 0, 20, 18, TILEMAPATTR_START);

	set_bkg_palette(0, 8, bkgPalette); // load palettes

	fadeout();

	// switch back to 1st video memory bank
	VBK_REG = 0;

	// set background map
	set_bkg_tiles(0, 0, 20, 18, TILEMAP_START);

	fadein();

   	while(joypad() != J_START) 
   	{
   		boardAnimation();
   		wait_vbl_done();
		gbt_update(); // This will change to ROM bank 1.
   	}

	//Stop the music
	gbt_stop();
	gbt_update();

	NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels

	winSound();

   	generateRandomBoard(board);
   	prev_color = board[0][0];

	//VBK_REG = 0;
	//set_bkg_tiles(0, 0, 20, 18, TILEMAP);
	transition();
	set_bkg_palette(0, 8, bkgPalette); // load palettes
	set_sprite_palette(0, 7, spritePalette); // load palettes
	VBK_REG = 1;
    set_bkg_tiles(1, 4, 1, 1, board[0]); 
    set_bkg_tiles(2, 4, 1, 1, board[0]);
	set_bkg_tiles(5, 3, 14, 14, board[0]);

	// switch to 2nd video memory bank
	/*VBK_REG = 1;*/

	// set background color palette map, do this first
	//set_win_tiles(0,0,20,2,tilemapWindowAttr);
	/*set_bkg_tiles(0, 0, 20, 18, TILEMAPATTR);*/
	/*set_bkg_tiles(5, 3, 14, 14, board[0]);*/
	/*set_bkg_tiles(1, 4, 1, 1, board[0]);*/
	/*set_bkg_tiles(2, 4, 1, 1, board[0]);*/

	// switch back to 1st video memory bank
	/*VBK_REG = 0; */

	// set background map
	/*set_bkg_tiles(0, 0, 20, 18, TILEMAP);*/
	//set_win_tiles(0,0,20,18,tilemapWindow);
	//set_bkg_tiles(5, 3, 14, 14, notRandom);    
	//set_bkg_tiles(5, 3, 14, 14, random[0]);
	//SHOW_BKG;
	//SHOW_WIN;

	set_sprite_tile(0, 2);
	set_sprite_tile(1, 1);
	set_sprite_tile(2, 0);
	set_sprite_tile(3, 0);
	set_sprite_tile(4, 0);
	set_sprite_tile(5, 0);
	set_sprite_tile(6, 0);

	move_sprite(0, 16, 60);
	move_sprite(1, 24, 60);
	move_sprite(2, 24, 76);
	move_sprite(3, 24, 92);
	move_sprite(4, 24, 108);
	move_sprite(5, 24, 124);
	move_sprite(6, 24, 140);
	move_sprite(7, 80, 20);
	move_sprite(8, 86, 20);

	set_sprite_prop(1, 0x00);
	set_sprite_prop(2, 0x01);
	set_sprite_prop(3, 0x02);
	set_sprite_prop(4, 0x03);
	set_sprite_prop(5, 0x04);
	set_sprite_prop(6, 0x05);

	//set_sprite_tile(1, 0);
	//move_sprite(1, 50, 50);

	setMoves(moves);

	SHOW_SPRITES;

	while(1) 
	{
		joypad_last = joypad_current;
  		joypad_current = joypad();
		if(BUTTON_TICKED(J_UP | J_LEFT)) 
		{
    		beepSound();
    		switch(color_state) 
    		{
            	case purple:
                	color_state = pink;
                	move_sprite(0, 16, 140);// Tile Number, Pos X + 8, Pos X + 16
                	set_sprite_tile(1,0);
                	set_sprite_tile(6,1);
                	break;
            	case blue:
                	color_state = purple;
            	    move_sprite(0, 16, 60);
                	set_sprite_tile(2,0);
            	    set_sprite_tile(1,1);
                	break;
            	case green:
	                color_state = blue;
    	            move_sprite(0, 16, 76);
        	        set_sprite_tile(3,0);
            	    set_sprite_tile(2,1);
                	break;
            	case yellow:
                	color_state = green;
	                move_sprite(0, 16, 92);
    	            set_sprite_tile(4,0);
        	        set_sprite_tile(3,1);
            	    break;
            	case red:
	                color_state = yellow;
    	            move_sprite(0, 16, 108);
        	        set_sprite_tile(5,0);
            	    set_sprite_tile(4,1);
                	break;
	            case pink:
    	            color_state = red;
        	        move_sprite(0, 16, 124);
            	    set_sprite_tile(6,0);
                	set_sprite_tile(5,1);
                	break;
        	}	
    	}

    	if(BUTTON_TICKED(J_DOWN | J_RIGHT)) 
    	{
    		beepSound();
    		switch(color_state) 
    		{
            	case purple:
                	color_state = blue;
                	move_sprite(0, 16, 76);
                	set_sprite_tile(1,0);
                	set_sprite_tile(2,1);
                	break;
            	case blue:
                	color_state = green;
                	move_sprite(0, 16, 92);
                	set_sprite_tile(2,0);
                	set_sprite_tile(3,1);
                	break;
            	case green:
                	color_state = yellow;
                	move_sprite(0, 16, 108);
                	set_sprite_tile(3,0);
                	set_sprite_tile(4,1);
                	break;
            	case yellow:
                	color_state = red;
                	move_sprite(0, 16, 124);
                	set_sprite_tile(4,0);
                	set_sprite_tile(5,1);
                	break;
            	case red:
                	color_state = pink;
                	move_sprite(0, 16, 140);
                	set_sprite_tile(5,0);
                	set_sprite_tile(6,1);
                	break;
            	case pink:
                	color_state = purple;
                	move_sprite(0, 16, 60);
                	set_sprite_tile(6,0);
                	set_sprite_tile(1,1);
                	break;
        	}	
    	}

    	if(BUTTON_TICKED(J_A | J_B)) 
    	{
    		if(prev_color != color_state) 
    		{
    			pewSound();
    			floodFill(0, 0, color_state, prev_color, board);
    			colorizeBoard(board);
    			prev_color = color_state;
    			if(checkWinner(prev_color, board) != 0)
    			{
					winSound();
					VBK_REG = 1;
    				set_win_tiles(0,0,20,18,WINNER_MAP_ATTR); 

    				VBK_REG = 0; 
    				set_win_tiles(0,0,20,18,WINNER_MAP);

    				HIDE_SPRITES;
					transition2();
    				SHOW_WIN;

    				waitpad(J_START);
    				
    				HIDE_WIN;
					winSound();
					transition();
    				SHOW_SPRITES;	
    				moves = 26;
    				setMoves(moves);
    				generateRandomBoard(board);
    				prev_color = board[0][0];
    				VBK_REG = 1;
    				set_bkg_tiles(5, 3, 14, 14, board[0]);
    				set_bkg_tiles(1, 4, 1, 1, board[0]); 
    				set_bkg_tiles(2, 4, 1, 1, board[0]);
    			}
    			moves--;
    			setMoves(moves); 
    			if(moves == 0)
    			{
					gameOverSound();
    				VBK_REG = 1;
    				set_win_tiles(0,0,20,18,LOSER_MAP_ATTR); 

    				VBK_REG = 0; 
    				set_win_tiles(0,0,20,18,LOSER_MAP);

    				HIDE_SPRITES;
					transition2();
    				SHOW_WIN;

    				waitpad(J_START);
    				
    				HIDE_WIN;
					winSound();
					transition();
    				SHOW_SPRITES;	
    				moves = 25;
    				setMoves(moves);
    				generateRandomBoard(board);
    				prev_color = board[0][0];
    				VBK_REG = 1;
    				set_bkg_tiles(5, 3, 14, 14, board[0]);
    				set_bkg_tiles(1, 4, 1, 1, board[0]); 
    				set_bkg_tiles(2, 4, 1, 1, board[0]);
    			}
    		}
    	}

    	wait_vbl_done();
	}
}

void generateRandomBoard(UINT8 board[14][14]) 
{
	// random generator based on 
	// https://stackoverflow.com/questions/66105001/how-can-you-get-a-random-number-on-gbdk
    int i, j;

    uint16_t seed = LY_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);

    for(i = 0; i<14; i++)
	{
        for(j = 0; j<14; j++)
        {	
        	UINT8 r = ((UINT8)rand()) % (UINT8)6;
            board[i][j] = r;
        }
    }
}

void floodFill(UINT8 x, UINT8 y, UINT8 new_col, UINT8 old_col, UINT8 board[14][14])
{
	//based on https://www.geeksforgeeks.org/flood-fill-algorithm-using-c-graphics/
	if(x > 13 || y > 13) 
	{
		return;
	}

    // check current pixel is old_color or not
    if (board[x][y] == old_col) 
    {
    	// put new pixel with new color
        board[x][y] = new_col;
 
        // recursive call for bottom pixel fill
        floodFill(x + 1, y, new_col, old_col, board);
 
        // recursive call for top pixel fill
        floodFill(x - 1, y, new_col, old_col, board);
 
        // recursive call for right pixel fill
        floodFill(x, y + 1, new_col, old_col, board);
 
        // recursive call for left pixel fill
        floodFill(x, y - 1, new_col, old_col, board);
    }
}

void colorizeBoard(UINT8 board[14][14])
{
	VBK_REG = 1; 
    set_bkg_tiles(5, 3, 14, 14, board[0]);
    set_bkg_tiles(1, 4, 1, 1, board[0]); 
    set_bkg_tiles(2, 4, 1, 1, board[0]);
}

int checkWinner(UINT8 color, UINT8 board[14][14]) 
{
	int i, j;

    for(i = 0; i<14; i++)
	{
        for(j = 0; j<14; j++)
        {	
        	if(board[i][j] != color)
        	{
        		return 0;
        	}
        }
    }

    return 1;	
}

void setMoves(UINT8 moves) 
{
	switch(moves)
	{
		case 25:
			set_sprite_tile(7, 5);
    		set_sprite_tile(8, 8);
        	break;
        case 24:
			set_sprite_tile(7, 5);
    		set_sprite_tile(8, 7);
        	break;
        case 23:
			set_sprite_tile(7, 5);
    		set_sprite_tile(8, 6);
        	break;
        case 22:
			set_sprite_tile(7, 5);
    		set_sprite_tile(8, 5);
            break;
        case 21:
			set_sprite_tile(7, 5);
    		set_sprite_tile(8, 4);
            break;
        case 20:
			set_sprite_tile(7, 5);
    		set_sprite_tile(8, 3);
            break;
        case 19:
			set_sprite_tile(7, 4);
    		set_sprite_tile(8, 12);
            break;
        case 18:
			set_sprite_tile(7, 4);
    		set_sprite_tile(8, 11);
            break;
        case 17:
			set_sprite_tile(7, 4);
    		set_sprite_tile(8, 10);
            break;
        case 16:
			set_sprite_tile(7, 4);
    		set_sprite_tile(8, 9);
            break;
        case 15:
			set_sprite_tile(7, 4);
    		set_sprite_tile(8, 8);
            break;
        case 14:
			set_sprite_tile(7, 4);
    		set_sprite_tile(8, 7);
            break;
        case 13:
			set_sprite_tile(7, 4);
    		set_sprite_tile(8, 6);
            break;                
        case 12:
			set_sprite_tile(7, 4);
    		set_sprite_tile(8, 5);
            break;              
        case 11:
			set_sprite_tile(7, 4);
    		set_sprite_tile(8, 4);
            break;              
        case 10:
			set_sprite_tile(7, 4);
    		set_sprite_tile(8, 3);
            break;
        case 9:
			set_sprite_tile(7, 3);
    		set_sprite_tile(8, 12);
            break;
        case 8:
			set_sprite_tile(7, 3);
    		set_sprite_tile(8, 11);
            break;               
        case 7:
			set_sprite_tile(7, 3);
    		set_sprite_tile(8, 10);
            break;             
        case 6:
			set_sprite_tile(7, 3);
    		set_sprite_tile(8, 9);
            break;    
        case 5:
			set_sprite_tile(7, 3);
    		set_sprite_tile(8, 8);
            break;    
        case 4:
			set_sprite_tile(7, 3);
    		set_sprite_tile(8, 7);
            break;    
        case 3:
			set_sprite_tile(7, 3);
    		set_sprite_tile(8, 6);
            break;    
        case 2:
			set_sprite_tile(7, 3);
    		set_sprite_tile(8, 5);
            break;    
        case 1:
			set_sprite_tile(7, 3);
    		set_sprite_tile(8, 4);
            break;
        case 0:
			set_sprite_tile(7, 3);
    		set_sprite_tile(8, 3);
            break;        
	}
}

void gameOverSound() 
{
	// Falling Down sound from https://www.gamedeveloper.com/programming/making-a-game-boy-game-in-2017-a-quot-sheep-it-up-quot-post-mortem-part-2-2-
	NR10_REG = 0x4F;
	NR11_REG = 0x96;
	NR12_REG = 0xB7;
	NR13_REG = 0xBB;
	NR14_REG = 0x85;
}

void winSound() 
{
	// Upgrade sound from https://github.com/drludos/GBcorp/blob/93fafb7d53b99beee0b96e8c2e8416ea02a2cbe6/gbcorp.c
	NR10_REG = 0x26;
	NR11_REG = 0x85;
	NR12_REG = 0xE0;
	NR13_REG = 0x84;
	NR14_REG = 0x00;
	NR14_REG = 0x83;
}

void pewSound() 
{
	// PEWPEW sound from https://gbdev.gg8.se/wiki/articles/Sound_tutorial
	NR10_REG = 0x1E;
	NR11_REG = 0x70;
	NR12_REG = 0xF3;
	NR13_REG = 0x00;
	NR14_REG = 0x87;
}

void beepSound() 
{
	// based on https://github.com/mrombout/gbdk_playground/tree/master/beep
	NR10_REG = 0x38;
    NR11_REG = 0x70;
    NR12_REG = 0xE0;
    NR13_REG = 0x0A;
    NR14_REG = 0xC6;
}

void boardAnimation() 
{
    int i, j;
    UINT8 board[8][8];

    for(i = 0; i<8; i++)
	{
        for(j = 0; j<8; j++)
        {	
        	UINT8 r = ((UINT8)rand()) % (UINT8)6;
	        board[i][j] = r;
        }
    }

    //delay(100);
	
    VBK_REG = 1; 
	set_bkg_tiles(6, 6, 8, 8, board[0]);
}

void onlyCGB() 
{
    if (_cpu != CGB_TYPE) 
	{
        enable_interrupts();
        set_bkg_tiles(0, 8, 20, 2, GBC_MESSAGE);
        SHOW_BKG;
        while(1) 
		{
            ASM_HALT; // Use less power while idle
        }
    }
}

void transition()
{
	UINT8 i, j, r;

	for(i = 0; i<18; i++)
	{
        for(j = 0; j<20; j++)
        {	
        	VBK_REG = 0;
			r = 0x02;
			set_bkg_tiles(j, i, 1, 1, &r);
			VBK_REG = 1;
			r = 0;
	        set_bkg_tiles(j, i, 1, 1, &r);
			r = (r + 1) % 5;
			set_bkg_tiles(j, i, 1, 1, &r);
			r = (r + 1) % 5;
			set_bkg_tiles(j, i, 1, 1, &r);
			r = (r + 1) % 5;
			set_bkg_tiles(j, i, 1, 1, &r);
			r = (r + 1) % 5;
			set_bkg_tiles(j, i, 1, 1, &r);
			r = (r + 1) % 5;
			set_bkg_tiles(j, i, 1, 1, &r);
			VBK_REG = 0;
			r = TILEMAP[j+(i*(UINT8)20)];
			set_bkg_tiles(j, i, 1, 1, &r);
			VBK_REG = 1;
			r = TILEMAPATTR[j+(i*(UINT8)20)];
			set_bkg_tiles(j, i, 1, 1, &r);
        }
    }
}

void transition2()
{
	UINT8 i, j;

	for(i = 0; i<18; i++)
	{
        for(j = 0; j<20; j++)
        {	
			set_bkg_tiles(j, i, 1, 1, 0x00);
        }
    }
}

INT16 DespRight(INT16 a, INT16 b) {
	return a >> b;
}

UWORD UpdateColor(UINT8 i, UWORD col) {
	//return RGB2(DespRight(PAL_RED(col), i), DespRight(PAL_GREEN(col), i), DespRight(PAL_BLUE(col), i));
	return RGB2(PAL_RED(col) | DespRight(0x1F, 5 - i), PAL_GREEN(col) | DespRight(0x1F, 5 - i), PAL_BLUE(col) | DespRight(0x1F, 5 - i));
}

void FadeStepColor(UINT8 i) {
	UINT8 pal, c;
	UWORD palette[4];
	UWORD palette_s[4];
	UWORD* col = ZGB_Fading_BPal;
	UWORD* col_s = ZGB_Fading_SPal;

	for(pal = 0; pal < 8; pal ++) {
		for(c = 0; c < 4; ++c, ++col, ++col_s) {
				palette[c] = UpdateColor(i, *col);
				palette_s[c] = UpdateColor(i, *col_s);
		};
		set_bkg_palette(pal, 1, palette);
		set_sprite_palette(pal, 1, palette_s);
	}
	delay(20);
}

void FadeInColor() {
	UINT8 i;
	for(i = 0; i != 6; i ++) {
		FadeStepColor(i);	
	}
}

void FadeOutColor() {
	UINT8 i;
	for(i = 5; i != 0xFF; -- i) {
		FadeStepColor(i);	
	}
}

void performantdelay(UINT8 numloops){
    UINT8 ii;
    for(ii = 0; ii < numloops; ii++){
        wait_vbl_done();
    }     
}

void fadeout(){
	UINT8 i;
	for(i=0;i<4;i++){
		switch(i){
			case 0:
				BGP_REG = 0xE4;
				break;
			case 1:
				BGP_REG = 0xF9;
				break;
			case 2:
				BGP_REG = 0xFE;
				break;
			case 3:
				BGP_REG = 0xFF;	
				break;						
		}
		performantdelay(7);
	}
}

void fadein(){
	UINT8 i;
	for(i=0;i<3;i++){
		switch(i){
			case 0:
				BGP_REG = 0xFE;
				break;
			case 1:
				BGP_REG = 0xF9;
				break;
			case 2:
				BGP_REG = 0xE4;
				break;					
		}
		performantdelay(7);
	}
}