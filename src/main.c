#include <gb/gb.h>
#include <gb/cgb.h> // Include cgb functions
#include <stdint.h>
#include <stdio.h>
#include <rand.h>
#include "utils.h"

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

	DISPLAY_ON;

	SPRITES_8x8;

	set_bkg_palette(0, 8, bkgPalette); // load palettes
	set_sprite_palette(0, 7, spritePalette); // load palettes
   	set_bkg_data(0, 74, TILESET); // load background tileset
   	//set_win_data(75, 1, TILESET);
	//set_bkg_tiles(0, 0, 20, 18, TILEMAP);
	set_sprite_data(0, 13, sprite);

	onlyCGB(); 

	VBK_REG = 1; 
	set_bkg_tiles(0, 0, 20, 18, TILEMAPATTR_START);
	VBK_REG = 0; 
   	set_bkg_tiles(0, 0, 20, 18, TILEMAP_START);
   	SHOW_BKG;

   	while(joypad() != J_START) 
   	{
   		boardAnimation();
   		wait_vbl_done();
   	}
   	transition();
   	HIDE_BKG;

   	generateRandomBoard(board);
   	prev_color = board[0][0];

	// switch to 2nd video memory bank
	VBK_REG = 1; 

	// set background color palette map, do this first
	//set_win_tiles(0,0,20,2,tilemapWindowAttr);
	set_bkg_tiles(0, 0, 20, 18, TILEMAPATTR);
	set_bkg_tiles(5, 3, 14, 14, board[0]);
	set_bkg_tiles(1, 4, 1, 1, board[0]); 
	set_bkg_tiles(2, 4, 1, 1, board[0]);

	// switch back to 1st video memory bank
	VBK_REG = 0; 

	// set background map
	set_bkg_tiles(0, 0, 20, 18, TILEMAP);
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
    					VBK_REG = 1;
    					set_win_tiles(0,0,20,18,WINNER_MAP_ATTR); 

    					VBK_REG = 0; 
    					set_win_tiles(0,0,20,18,WINNER_MAP);

    					HIDE_SPRITES;
    					SHOW_WIN;

    					waitpad(J_START);
    				
    					HIDE_WIN;
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
    					VBK_REG = 1;
    					set_win_tiles(0,0,20,18,LOSER_MAP_ATTR); 

    					VBK_REG = 0; 
    					set_win_tiles(0,0,20,18,LOSER_MAP);

    					HIDE_SPRITES;
    					SHOW_WIN;

    					waitpad(J_START);
    				
    					HIDE_WIN;
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

void pewSound() 
{
	// PEWPEW sound from https://gbdev.gg8.se/wiki/articles/Sound_tutorial
	NR10_REG = 0x1E;
	NR11_REG = 0x10;
	NR12_REG = 0xF3;
	NR13_REG = 0x00;
	NR14_REG = 0x87;
}

void beepSound() 
{
	// based on https://github.com/mrombout/gbdk_playground/tree/master/beep
	NR10_REG = 0x38U;
    	NR11_REG = 0x70U;
    	NR12_REG = 0xE0U;
    	NR13_REG = 0x0AU;
    	NR14_REG = 0xC6U;

    	NR51_REG |= 0x11;
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
    	if (_cpu != CGB_TYPE) {
        	enable_interrupts();
        	set_bkg_tiles(0, 8, 20, 2, GBC_MESSAGE);
        	SHOW_BKG;
        	while(1) {
            		ASM_HALT; // Use less power while idle
        	}
    	}
}

void transition()
{
	UINT8 blank[20] = {
  	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	};

	UINT8 i;

	VBK_REG = 0; 

	for(i = 0; i<18; i++)
	{
		set_bkg_tiles(0, i, 20, 1, blank);
	}
}