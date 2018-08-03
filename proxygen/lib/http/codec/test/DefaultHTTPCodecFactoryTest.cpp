/*
 *  Copyright (c) 2018-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#include <folly/portability/GTest.h>
#include <limits>
#include <proxygen/lib/http/codec/DefaultHTTPCodecFactory.h>
#include <proxygen/lib/http/codec/HTTP2Constants.h>
#include <proxygen/lib/http/codec/HTTP1xCodec.h>
#include <proxygen/lib/http/codec/SPDYCodec.h>
#include <proxygen/lib/http/codec/HTTP2Codec.h>

using namespace proxygen;
using namespace testing;


TEST(DefaultHTTPCodecFactoryTest, getCodec) {
  DefaultHTTPCodecFactory factory(false);
  auto codec = factory.getCodec("spdy/3.1", TransportDirection::UPSTREAM, true);
  SPDYCodec* spdyCodec = dynamic_cast<SPDYCodec*>(codec.get());
  EXPECT_TRUE(spdyCodec != nullptr);

  codec = factory.getCodec(http2::kProtocolString, TransportDirection::UPSTREAM, true);
  HTTP2Codec* http2Codec = dynamic_cast<HTTP2Codec*>(codec.get());
  EXPECT_TRUE(http2Codec != nullptr);

  codec = factory.getCodec("http/1.1", TransportDirection::UPSTREAM, true);
  HTTP1xCodec* http1xCodec = dynamic_cast<HTTP1xCodec*>(codec.get());
  EXPECT_TRUE(http1xCodec != nullptr);

  codec = factory.getCodec("", TransportDirection::UPSTREAM, true);
  http1xCodec = dynamic_cast<HTTP1xCodec*>(codec.get());
  EXPECT_TRUE(http1xCodec != nullptr);

  codec = factory.getCodec("not/supported", TransportDirection::UPSTREAM, true);
  http1xCodec = dynamic_cast<HTTP1xCodec*>(codec.get());
  EXPECT_TRUE(http1xCodec != nullptr);
}