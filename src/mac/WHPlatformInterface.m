//
// WHPlatformInterface.m
// Harmony
//

#include <stdlib.h>

#include "plat_interface.h"

char * hplat_get_script_path() {
	// Use a separate autorelease pool for callbacks into Objective-C.
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	// Get the script path.
	NSString * path = [[[[[NSBundle mainBundle] resourceURL] absoluteURL] path]
		stringByAppendingString:@"/script/?.lua"];
	
	// Allocate the buffer and copy in the path.
	size_t len = [path lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
	char * buffer = (char *)malloc(len + 1);
	[path getCString:buffer maxLength:(len + 1) encoding:NSUTF8StringEncoding];
	
	// Drain the pool and return. The caller must free the buffer.
	[pool drain];
	return buffer;
}

char * hplat_read_text_file(const char * filename) {
	// Use a separate autorelease pool for callbacks into Objective-C.
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	// Get the file's URL.
	NSURL * file = [[[NSBundle mainBundle] resourceURL]
		URLByAppendingPathComponent:[NSString stringWithUTF8String:filename]];
	
	// Get the file's text.
	NSString * contents = [NSString stringWithContentsOfURL:file
		encoding:NSUTF8StringEncoding error:NULL];
	
	// Allocate the buffer and copy in the text.
	char * buffer = NULL;
	if (contents) {
		const char * encodedContents = [contents UTF8String];
		size_t len = strlen(encodedContents);
		buffer = (char *)malloc(len + 1);
		strncpy(buffer, encodedContents, len);
		buffer[len] = '\0';
	}
	
	// Drain the pool and return. The caller must free the buffer.
	[pool drain];
	return buffer;
}

void * hplat_read_texture_file(const char * filename,
		size_t * outImageWidth, size_t * outImageHeight,
		size_t * outTextureWidth, size_t * outTextureHeight) {
	// Use a separate autorelease pool for callbacks into Objective-C.
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	// Get the file's URL.
	NSURL * file = [[[NSBundle mainBundle] resourceURL]
		URLByAppendingPathComponent:[NSString stringWithUTF8String:filename]];
	
	// Open the image.
	CGImageSourceRef imageSource = CGImageSourceCreateWithURL((CFURLRef)file, NULL);
	CGImageRef image = CGImageSourceCreateImageAtIndex(imageSource, 0, NULL);
	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	
	// Get the image's metrics.
	size_t width = CGImageGetWidth(image), height = CGImageGetHeight(image);
	CGRect bounds = {{0, 0}, {width, height}};
	
	// If the client requested the metrics, provide them.
	if (outImageWidth) *outImageWidth = width;
	if (outImageHeight) *outImageHeight = height;
	if (outTextureWidth) *outTextureWidth = width;
	if (outTextureHeight) *outTextureHeight = height;
	
	// Allocate the buffer and copy in the image.
	void * buffer = malloc(width * height * 4);
	CGContextRef context = CGBitmapContextCreate(buffer, width, height, 8, width * 4,
		colorSpace, kCGBitmapByteOrder32Host | kCGImageAlphaPremultipliedFirst);
	CGContextDrawImage(context, bounds, image);
	
	// Drain the pool and return. The caller must free the buffer.
	CGContextRelease(context);
	CGColorSpaceRelease(colorSpace);
	CGImageRelease(image);
	CFRelease(imageSource);
	[pool drain];
	return buffer;
}
