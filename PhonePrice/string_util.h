/*
 * Copyright 2013 360.cn. All Rights Reserved.
 * =====================================================================================
 * Filename:  string_util.h
 * Description:   description
 * Author:  Koth(Yaowen Chen)
 *
 */
#ifndef STRING_UTIL_H_
#define STRING_UTIL_H_
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <string.h>

typedef unsigned short  UnicodeCharT;
typedef std::basic_string<UnicodeCharT> UnicodeStr;

class StringUtil {
public:
  static bool u8tou16(const char *src, size_t len, UnicodeStr &dest) {
    if (src == NULL)
      return true;
    UnicodeCharT stackBuf[1024] = { 0 };
    size_t out_len = len;
    UnicodeCharT *destBuf = NULL;
    if (out_len > 1024) {
      destBuf = new UnicodeCharT[out_len];
    } else {
      destBuf = stackBuf;
    }
    if (destBuf == NULL)
      return false;
    size_t j = 0;
    unsigned char ubuf[2] = { 0 };
    for (size_t i = 0; i < len && j < out_len;) {
      unsigned char ch = (src[i] & 0xFF);
      if (ch < (unsigned short) 0x80) {
        destBuf[j++] = (ch & 0x7F);
        i += 1;
      } else if (ch < (unsigned short) 0xC0) {
        //need skip this guy!!!0x10xxxxxx, invalid start of utf-8 sequence!!
        destBuf[j++] = 0x3f;//switch it into '?'
        i += 1;
      } else if (ch < (unsigned short) 0xE0 && i + 1 < len) {
        //110xxxxx 10xxxxxx
        ubuf[1] = (((ch & 0x1C) >> 2) & 0x7);
        ubuf[0] = ((((ch & 0x3) << 6)) | ((src[i + 1]) & 0x3F)) & 0xFF;
        destBuf[j++] = *((UnicodeCharT *) &ubuf[0]);
        i += 2;
      } else if (ch < (unsigned short) 0xF0 && i + 2 < len) {
        //1110xxxx 10xxxxxx 10xxxxxx
        ubuf[1] = ((((ch & 0x0F) << 4) | ((src[i + 1] & 0x3C) >> 2))
                   & 0xFF);
        ubuf[0] = ((((src[i + 1] & 0x3) << 6)) | ((src[i + 2]) & 0x3F))
                  & 0xFF;
        destBuf[j++] = *((UnicodeCharT *) &ubuf[0]);
        i += 3;
      } else if (ch < (unsigned short) 0xF8) {
        destBuf[j++] = 0x3f;//switch it into '?'
        i += 4;
      } else if (ch < (unsigned short) 0xFC) {
        destBuf[j++] = 0x3f;//switch it into '?'
        i += 5;
      } else if (ch < (unsigned short) 0xFE) {
        destBuf[j++] = 0x3f;//switch it into '?'
        i += 6;
      } else { //0xFF
        destBuf[j++] = 0x3f;
        i += 1;
      }
    }

    dest.assign(destBuf, j);
    if (destBuf != stackBuf)
      delete[] destBuf;
    return (j > 0);
  }

  static bool u16tou8(const UnicodeCharT *src, size_t len, std::string &dest) {
    if (src == NULL)
      return true;
    char stackBuf[1024] = { 0 };
    size_t out_len = len * 3;
    char *destBuf = NULL;
    if (out_len > 1024) {
      destBuf = new char[out_len];
    } else {
      destBuf = stackBuf;
    }
    if (destBuf == NULL)
      return false;
    size_t j = 0;
    for (size_t i = 0; i < len && j < out_len; i++) {
      unsigned short uch = src[i];
      if (uch < (unsigned short) 0x7F) {
        destBuf[j++] = (uch & 0x007F);
      } else if (uch < (unsigned short) 0x7FF) {
        //110xxxxx 10xxxxxx
        destBuf[j++] = ((((uch & 0x03C0) >> 6) & 0xFF) | (0xC0)) & 0xFF;
        destBuf[j++] = ((uch & 0x3F) | (0x80)) & 0xFF;
      } else {
        //1110xxxx 10xxxxxx 10xxxxxx
        destBuf[j++] = ((((uch & 0xF000) >> 12) & 0xFF) | (0xE0))
                       & 0xFF;
        destBuf[j++] = ((((uch & 0x0FC0) >> 6) & 0xFF) | (0x80)) & 0xFF;
        destBuf[j++] = ((uch & 0x3F) | (0x80)) & 0xFF;
      }
    }
    dest.assign(destBuf, j);
    if (destBuf != stackBuf)
      delete[] destBuf;
    return (j > 0);
  }

  static int SplitString(const char *str, size_t len,
                         char sepChar, std::vector<std::string> *pOut) {
    const char *ptr = str;
    if (ptr == NULL || len == 0) {
      return 0;
    }
    size_t start = 0;
    while (start < len && (str[start] == sepChar)) {
      start += 1;
    }
    ptr = str + start;
    len = len - start;
    while (len > 0 && ptr[len - 1] == sepChar) {
      len -= 1;
    }
    if (len <= 0) {
      return 0;
    }
    size_t ps = 0;
    int nret = 0;
    for (size_t i = 0; i < len; i++) {
      if (ptr[i] == sepChar) {
        if (ptr[i - 1] != sepChar) {
          std::string ts(ptr + ps, i - ps);
          pOut->push_back(ts);
          nret += 1;
        }
        ps = i + 1;
      }
    }
    if (ps < len) {
      pOut->push_back(std::string(ptr + ps, len - ps));
      nret += 1;
    }
    return nret;
  }
};

#endif  // STRING_UTIL_H_
