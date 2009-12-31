//
// WHPlatformInterface.cpp
// Harmony
//

#include "WHGlue.h"
#include "plat_interface.h"

static WCHAR * WHCreateWideStringFromUTF8(const char * str) {
	// Get the size of the wide string.
	int size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str, -1, NULL, 0);

	// Allocate the wide string buffer.
	WCHAR * buffer = reinterpret_cast<WCHAR *>(malloc(size * sizeof(WCHAR)));

	// Copy the string into that buffer.
	if (!MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str, -1, buffer, size)) {
		free(buffer);
		buffer = NULL;
	}
	
	// The caller must free the buffer.
	return buffer;
}

static unsigned WHConvertToTextureDimension(unsigned x) {
	if ((x & (x - 1)) == 0) {
		// Already a power of two.
		return x;
	} else {
		// Return the next largest power of two.
		x |= (x >> 1);
        x |= (x >> 2);
        x |= (x >> 4);
        x |= (x >> 8);
        x |= (x >> 16);
        return x + 1;
	}
}

char * hplat_get_script_path() {
/*
#if NDEBUG
	static const char path[] = "!\\script\\?.lua";
	
	// Allocate the buffer and copy in the path.
	char * buffer = reinterpret_cast<char *>(malloc(sizeof(path)));
	strcpy_s(buffer, sizeof(path), path);
#else
	...
#endif
*/
	static const char suffix[] = "/script/?.lua";

	// Allocate the buffer and read in the path.
	size_t len = GetCurrentDirectoryA(0, NULL) + sizeof(suffix);
	char * buffer = reinterpret_cast<char *>(malloc(len));
	GetCurrentDirectoryA(len, buffer);

	// Append the script search path.
	strcat_s(buffer, len, suffix);

	// The caller must free the buffer.
	return buffer;
}

char * hplat_read_text_file(const char * filename) {
	// Open the file.
	WCHAR * path = WHCreateWideStringFromUTF8(filename);
	CFile file(path, CFile::modeRead | CFile::shareDenyWrite);
	free(path);

	// Allocate the buffer and read in the text.
	size_t len = static_cast<size_t>(file.GetLength());
	char * buffer = reinterpret_cast<char *>(malloc(len + 1));
	len = file.Read(buffer, len);
	buffer[len] = '\0';

	// The caller must free the buffer.
	return buffer;
}

void * hplat_read_texture_file(const char * filename,
		size_t * outImageWidth, size_t * outImageHeight,
		size_t * outTextureWidth, size_t * outTextureHeight) {
	// Open the image.
	WCHAR * path = WHCreateWideStringFromUTF8(filename);
	Gdiplus::Bitmap image(path, FALSE);
	free(path);
	
	// Get the image's metrics.
	size_t imageWidth = image.GetWidth(), imageHeight = image.GetHeight();
	Gdiplus::Rect bounds(0, 0, imageWidth, imageHeight);

	// Windows can't handle textures whose sides aren't powers of two.
	size_t textureWidth = WHConvertToTextureDimension(imageWidth);
	size_t textureHeight = WHConvertToTextureDimension(imageWidth);

	// If the client requested the metrics, provide them.
	if (outImageWidth) *outImageWidth = imageWidth;
	if (outImageHeight) *outImageHeight = imageHeight;
	if (outTextureWidth) *outTextureWidth = textureWidth;
	if (outTextureHeight) *outTextureHeight = textureHeight;

	// Allocate the buffer.
	Gdiplus::BitmapData data;
	data.Width = textureWidth;
	data.Height = textureHeight;
	data.Stride = textureWidth * 4;
	data.PixelFormat = PixelFormat32bppARGB;
	data.Scan0 = malloc(textureWidth * textureHeight * 4);

	// Copy in the image.
	image.LockBits(&bounds, Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeUserInputBuf, data.PixelFormat, &data);
	image.UnlockBits(&data);

	// The caller must free the buffer.
	return data.Scan0;
}
