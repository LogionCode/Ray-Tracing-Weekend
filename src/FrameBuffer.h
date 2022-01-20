#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

class FrameBuffer {
public:
	static constexpr size_t kBytesPerPixel = 3;

	FrameBuffer(size_t width, size_t height) :
		width_(width),
		height_(height),
		data_((uint8_t*)(malloc(width* height* kBytesPerPixel))) {};

	~FrameBuffer() { free(data_); };

	void setPixel(size_t row, size_t col,
		uint8_t r, uint8_t g, uint8_t b) {

		const size_t idx = kBytesPerPixel * (row * width_ + col);
		data_[idx + 0] = b;
		data_[idx + 1] = g;
		data_[idx + 2] = r;
	}

	void save(const char* filePath) {
		FILE* fptr = fopen(filePath, "wb");
		assert(fptr); //stops if failed
		putc(0, fptr);
		putc(0, fptr);
		putc(2, fptr);                         /* uncompressed RGB */
		putc(0, fptr); putc(0, fptr);
		putc(0, fptr); putc(0, fptr);
		putc(0, fptr);
		putc(0, fptr); putc(0, fptr);           /* X origin */
		putc(0, fptr); putc(0, fptr);           /* y origin */
		putc((width_ & 0x00FF), fptr);
		putc((width_ & 0xFF00) / 256, fptr);
		putc((height_ & 0x00FF), fptr);
		putc((height_ & 0xFF00) / 256, fptr);
		putc(24, fptr);                        /* 24 bit bitmap */
		putc(0, fptr);
		fwrite(data_, kBytesPerPixel, width_ * height_, fptr);
		fclose(fptr);
	}

	size_t width() const { return width_; }
	size_t height() const { return height_; }
private:
	uint8_t* data_;
	size_t width_;
	size_t height_;
};
