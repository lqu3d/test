#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <FreeImage.h>
#include <stdio.h>
CResMgr::CResMgr()
{
}

void CResMgr::OnAppInit(){

}

GLint CResMgr::LoadShader(const char* vsfile, const char*psfile) {
	using namespace std;

	GLint vsid = glCreateShader(GL_VERTEX_SHADER);
	GLint psid = glCreateShader(GL_FRAGMENT_SHADER);
	
	std::string vsstr, psstr;
	xTextFromFile(vsfile, vsstr);
	xTextFromFile(psfile, psstr);
	const char* vsStrArr[] = { vsstr.c_str() };
	const char* psStrArr[] = { psstr.c_str() };

	GLint compResult = GL_FALSE, errInfoLen = 0;

	std::cout << "Compiling vertex shader: " << vsfile << std::endl;
	glShaderSource(vsid, 1, vsStrArr, NULL);
	glCompileShader(vsid);

	glGetShaderiv(vsid, GL_COMPILE_STATUS, &compResult);
	glGetShaderiv(vsid, GL_INFO_LOG_LENGTH, &errInfoLen);
	if (!compResult && errInfoLen > 1) {
		char* errStr = new char[errInfoLen];
		glGetShaderInfoLog(vsid, errInfoLen, NULL, errStr);
		xMsg(vsfile, errStr, MB_ICONERROR);

		delete[] errStr;
		return 0;
	}

	std::cout << "Compiling fragment shader: " << psfile << std::endl;
	glShaderSource(psid, 1, psStrArr, NULL);
	glCompileShader(psid);

	glGetShaderiv(psid, GL_COMPILE_STATUS, &compResult);
	glGetShaderiv(psid, GL_INFO_LOG_LENGTH, &errInfoLen);
	if (!compResult && errInfoLen > 1) {
		char* errStr = new char[errInfoLen];
		glGetShaderInfoLog(psid, errInfoLen, NULL, errStr);
		xMsg(psfile, errStr, MB_ICONERROR);

		delete[] errStr;
		return 0;
	}

	std::cout << "Linking programe" << std::endl;
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vsid);
	glAttachShader(programId, psid);
	glLinkProgram(programId);

	glDetachShader(programId, vsid);
	glDetachShader(programId, psid);

	glDeleteShader(vsid);
	glDeleteShader(psid);

	return programId;
}


//参照FreeImage官网给出的CTextrueManager写的加载函数
//官方给的例子是用opengl3.0以下的旧GL写的，没有使用glGenerateMipmap(GL_TEXTURE_2D)来产生mipmap
//在GL3.0以后，默认是开启了MIPMAP的，如果不调用glGenerateMipmap来生成MIPMAP，则渲染出的贴图一片黑色
//另外要注意freeimage的颜色分量顺序是gbr,不知为什么，故这里fmt应传GL_BGR
GLuint CResMgr::LoadTextrue(const char* texFile, GLenum fmt, GLuint ifmt, GLuint level, GLuint border) {
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(texFile, 0);
	if (fifmt == FIF_UNKNOWN) {
		fifmt = FreeImage_GetFIFFromFilename(texFile);
		if (fifmt == FIF_UNKNOWN) {
			xsMsg(texFile, "图片加载失败:未知的格式", MB_ICONERROR);
			return 0;
		}
	}

	if (!FreeImage_FIFSupportsReading(fifmt)) {
		xMsg(texFile, "freeImage不支持该文件格式的读取", MB_ICONERROR);
		return 0;
	}

	FIBITMAP* dib = FreeImage_Load(fifmt, texFile);
	if (!dib) {
		xMsg(texFile, "freeImage_load失败", MB_ICONERROR);
		return 0;
	}

	BYTE* bits = FreeImage_GetBits(dib);
	GLuint width = FreeImage_GetWidth(dib);
	GLuint height = FreeImage_GetHeight(dib);

	if (!bits || width == 0 || height == 0) {
		xMsg(texFile, "freeImage_getbits, getwidth, getheight-failed", MB_ICONERROR);
		return 0;
	}

	GLuint texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, level, ifmt, width, height, border, fmt, GL_UNSIGNED_BYTE, bits);
	
	glGenerateMipmap(GL_TEXTURE_2D); //注意，不加这句渲染出的贴图是一片黑色，
	FreeImage_Unload(dib);
	return texId;
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT 0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3

GLuint CResMgr::loadDDS(const char * imagepath) {

	unsigned char header[124];

	FILE *fp;

	/* try to open the file */
	fp = fopen(imagepath, "rb");
	if (fp == NULL) {
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar();
		return 0;
	}

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		return 0;
	}

	/* get the surface desc */
	fread(&header, 124, 1, fp);

	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);


	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	/* close the file pointer */
	fclose(fp);

	unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if (width < 1) width = 1;
		if (height < 1) height = 1;

	}

	free(buffer);

	return textureID;


}
void CResMgr::OnAppQuit(){

}

CResMgr::~CResMgr()
{
}
