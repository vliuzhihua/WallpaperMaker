#include "stdafx.h"
#define cimg_using_png
#include "CImg.h"
#ifndef cimg_imagepath
#define cimg_imagepath "img/"
#endif
#undef min
#undef max

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>

// Main procedure
//---------------
int main(int argc, char **argv) {

	// Read and check command line parameters.
	cimg_usage("Compute a linear fading between two 2D images");

	// Init images.
	cil::CImg<unsigned char> target_img;
	target_img.resize(512, 512, 1, 3);
	target_img.get_channel(0).fill(0);
	target_img.get_channel(1).fill(120);
	target_img.get_channel(2).fill(255);
	target_img.get_shared_channel(0).fill(0);
	target_img.get_shared_channel(1).fill(122);
	target_img.get_shared_channel(2).fill(44);
	//target_img.display("re");
	//target_img.assign().fill(0);
	//target_img.norm().resize(512, 512);
	cil::CImg<unsigned char> font_img;
	//font_img.load_jpeg
	//font_img.load_jp
	//font_img.assign().load_bu

	FT_Library    pFTLib = NULL;
	FT_Face        pFTFace = NULL;
	FT_Error    error = 0;
	//Init FreeType Lib to manage memory
	error = FT_Init_FreeType(&pFTLib);
	if (error)
	{
		pFTLib = 0;
		printf(" There is some error when Init Library ");
		return   -1;
	}

	//create font face from font file
	//error = FT_New_Face(pFTLib, "msyh.ttf", 0, &pFTFace);
	error = FT_New_Face(pFTLib, "simkai.ttf", 0, &pFTFace);
	if (!error)
	{
		FT_Set_Char_Size(pFTFace, 16 << 8, 16 << 8, 300, 300);
		FT_Glyph    glyph;
		//  load glyph 'C'
		//FT_Load_Glyph(pFTFace, FT_Get_Char_Index(pFTFace, 67), FT_LOAD_DEFAULT);
		//FT_Load_Glyph(pFTFace, FT_Get_Char_Index(pFTFace, L'ºÚ'), FT_LOAD_DEFAULT);
		FT_Load_Glyph(pFTFace, FT_Get_Char_Index(pFTFace, L'ºÚ'), FT_LOAD_COLOR);
		//FT_Load_Char(pFTFace, L'ºÚ', FT_LOAD_RENDER); 
		error = FT_Get_Glyph(pFTFace->glyph, &glyph);
		if (!error)
		{
			//  convert glyph to bitmap with 256 gray
			FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
			FT_BitmapGlyph    bitmap_glyph = (FT_BitmapGlyph)glyph;
			FT_Bitmap &     bitmap = bitmap_glyph->bitmap;

			font_img = cil::CImg<unsigned char>(bitmap.buffer, bitmap.width, bitmap.rows, 1, 1);
			//target_img.assign().draw_i
			//target_img.save("result.png");
			//font_img.display("result");
			target_img.draw_image(100, 100, font_img);
			//target_img.display("result");
			
			//for (int i = 0; i < bitmap.rows; ++i)
			//{
			//	for (int j = 0; j < bitmap.width; ++j)
			//	{
			//		//  if it has gray>0 we set show it as 1, o otherwise
			//		printf(" %d ", bitmap.buffer[i * bitmap.width + j] ? 1 : 0);
			//	}
			//	printf(" \n");
			//}
			//  free glyph
			FT_Done_Glyph(glyph);
			glyph = NULL;
		}
		//  free face
		FT_Done_Face(pFTFace);
		pFTFace = NULL;
	}

	//  free FreeType Lib
	FT_Done_FreeType(pFTLib);
	pFTLib = NULL;


	//char* tt;
	//cil::CImg<> im(tt, 100, 100, 1, 4);
	////target_img.assign().draw_i
	target_img.save("result.bmp");
	//target_img.display("result");
}
