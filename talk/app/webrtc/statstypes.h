/*
 * libjingle
 * Copyright 2012 Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// This file contains structures used for retrieving statistics from an ongoing
// libjingle session.

#ifndef TALK_APP_WEBRTC_STATSTYPES_H_
#define TALK_APP_WEBRTC_STATSTYPES_H_

#include <algorithm>
#include <list>
#include <string>
#include <vector>

#include "webrtc/base/basictypes.h"
#include "webrtc/base/linked_ptr.h"
#include "webrtc/base/scoped_ptr.h"
#include "webrtc/base/common.h"
#include "webrtc/base/linked_ptr.h"
#include "webrtc/base/scoped_ptr.h"
#include "webrtc/base/stringencode.h"

namespace webrtc {

class StatsReport {
 public:
  // Indicates whether a track is for sending or receiving.
  // Used in reports for audio/video tracks.
  enum Direction {
    kSend = 0,
    kReceive,
  };

  enum StatsType {
    // StatsReport types.
    // A StatsReport of |type| = "googSession" contains overall information
    // about the thing libjingle calls a session (which may contain one
    // or more RTP sessions.
    kStatsReportTypeSession,

    // A StatsReport of |type| = "googTransport" contains information
    // about a libjingle "transport".
    kStatsReportTypeTransport,

    // A StatsReport of |type| = "googComponent" contains information
    // about a libjingle "channel" (typically, RTP or RTCP for a transport).
    // This is intended to be the same thing as an ICE "Component".
    kStatsReportTypeComponent,

    // A StatsReport of |type| = "googCandidatePair" contains information
    // about a libjingle "connection" - a single source/destination port pair.
    // This is intended to be the same thing as an ICE "candidate pair".
    kStatsReportTypeCandidatePair,

    // A StatsReport of |type| = "VideoBWE" is statistics for video Bandwidth
    // Estimation, which is global per-session.  The |id| field is "bweforvideo"
    // (will probably change in the future).
    kStatsReportTypeBwe,

    // A StatsReport of |type| = "ssrc" is statistics for a specific rtp stream.
    // The |id| field is the SSRC in decimal form of the rtp stream.
    kStatsReportTypeSsrc,

    // A StatsReport of |type| = "remoteSsrc" is statistics for a specific
    // rtp stream, generated by the remote end of the connection.
    kStatsReportTypeRemoteSsrc,

    // A StatsReport of |type| = "googTrack" is statistics for a specific media
    // track. The |id| field is the track id.
    kStatsReportTypeTrack,

    // A StatsReport of |type| = "localcandidate" or "remotecandidate" is
    // attributes on a specific ICE Candidate. It links to its connection pair
    // by candidate id. The string value is taken from
    // http://w3c.github.io/webrtc-stats/#rtcstatstype-enum*.
    kStatsReportTypeIceLocalCandidate,
    kStatsReportTypeIceRemoteCandidate,

    // A StatsReport of |type| = "googCertificate" contains an SSL certificate
    // transmitted by one of the endpoints of this connection.  The |id| is
    // controlled by the fingerprint, and is used to identify the certificate in
    // the Channel stats (as "googLocalCertificateId" or
    // "googRemoteCertificateId") and in any child certificates (as
    // "googIssuerId").
    kStatsReportTypeCertificate,

    // A StatsReport of |type| = "datachannel" with statistics for a
    // particular DataChannel.
    kStatsReportTypeDataChannel,
  };

  enum StatsValueName {
    kStatsValueNameActiveConnection,
    kStatsValueNameAudioInputLevel,
    kStatsValueNameAudioOutputLevel,
    kStatsValueNameBytesReceived,
    kStatsValueNameBytesSent,
    kStatsValueNameDataChannelId,
    kStatsValueNamePacketsLost,
    kStatsValueNamePacketsReceived,
    kStatsValueNamePacketsSent,
    kStatsValueNameProtocol,
    kStatsValueNameReadable,
    kStatsValueNameSsrc,
    kStatsValueNameState,
    kStatsValueNameTransportId,

    // Internal StatsValue names.
    kStatsValueNameActualEncBitrate,
    kStatsValueNameAdaptationChanges,
    kStatsValueNameAvailableReceiveBandwidth,
    kStatsValueNameAvailableSendBandwidth,
    kStatsValueNameAvgEncodeMs,
    kStatsValueNameBandwidthLimitedResolution,
    kStatsValueNameBucketDelay,
    kStatsValueNameCaptureJitterMs,
    kStatsValueNameCaptureQueueDelayMsPerS,
    kStatsValueNameCaptureStartNtpTimeMs,
    kStatsValueNameCandidateIPAddress,
    kStatsValueNameCandidateNetworkType,
    kStatsValueNameCandidatePortNumber,
    kStatsValueNameCandidatePriority,
    kStatsValueNameCandidateTransportType,
    kStatsValueNameCandidateType,
    kStatsValueNameChannelId,
    kStatsValueNameCodecName,
    kStatsValueNameComponent,
    kStatsValueNameContentName,
    kStatsValueNameCpuLimitedResolution,
    kStatsValueNameCurrentDelayMs,
    kStatsValueNameDecodeMs,
    kStatsValueNameDecodingCNG,
    kStatsValueNameDecodingCTN,
    kStatsValueNameDecodingCTSG,
    kStatsValueNameDecodingNormal,
    kStatsValueNameDecodingPLC,
    kStatsValueNameDecodingPLCCNG,
    kStatsValueNameDer,
    kStatsValueNameEchoCancellationQualityMin,
    kStatsValueNameEchoDelayMedian,
    kStatsValueNameEchoDelayStdDev,
    kStatsValueNameEchoReturnLoss,
    kStatsValueNameEchoReturnLossEnhancement,
    kStatsValueNameEncodeUsagePercent,
    kStatsValueNameExpandRate,
    kStatsValueNameFingerprint,
    kStatsValueNameFingerprintAlgorithm,
    kStatsValueNameFirsReceived,
    kStatsValueNameFirsSent,
    kStatsValueNameFrameHeightInput,
    kStatsValueNameFrameHeightReceived,
    kStatsValueNameFrameHeightSent,
    kStatsValueNameFrameRateDecoded,
    kStatsValueNameFrameRateInput,
    kStatsValueNameFrameRateOutput,
    kStatsValueNameFrameRateReceived,
    kStatsValueNameFrameRateSent,
    kStatsValueNameFrameWidthInput,
    kStatsValueNameFrameWidthReceived,
    kStatsValueNameFrameWidthSent,
    kStatsValueNameInitiator,
    kStatsValueNameIssuerId,
    kStatsValueNameJitterBufferMs,
    kStatsValueNameJitterReceived,
    kStatsValueNameLabel,
    kStatsValueNameLocalAddress,
    kStatsValueNameLocalCandidateId,
    kStatsValueNameLocalCandidateType,
    kStatsValueNameLocalCertificateId,
    kStatsValueNameMaxDecodeMs,
    kStatsValueNameMinPlayoutDelayMs,
    kStatsValueNameNacksReceived,
    kStatsValueNameNacksSent,
    kStatsValueNamePlisReceived,
    kStatsValueNamePlisSent,
    kStatsValueNamePreferredJitterBufferMs,
    kStatsValueNameRecvPacketGroupArrivalTimeDebug,
    kStatsValueNameRecvPacketGroupPropagationDeltaDebug,
    kStatsValueNameRecvPacketGroupPropagationDeltaSumDebug,
    kStatsValueNameRemoteAddress,
    kStatsValueNameRemoteCandidateId,
    kStatsValueNameRemoteCandidateType,
    kStatsValueNameRemoteCertificateId,
    kStatsValueNameRenderDelayMs,
    kStatsValueNameRetransmitBitrate,
    kStatsValueNameRtt,
    kStatsValueNameSendPacketsDiscarded,
    kStatsValueNameTargetDelayMs,
    kStatsValueNameTargetEncBitrate,
    kStatsValueNameTrackId,
    kStatsValueNameTransmitBitrate,
    kStatsValueNameTransportType,
    kStatsValueNameTypingNoiseState,
    kStatsValueNameViewLimitedResolution,
    kStatsValueNameWritable,
  };

  class Id {
   public:
    virtual ~Id();
    StatsType type() const;
    virtual bool Equals(const Id& other) const;
    virtual std::string ToString() const = 0;

   protected:
    Id(StatsType type);  // Only meant for derived classes.
    const StatsType type_;
  };

  struct Value {
    Value(StatsValueName name, const std::string& value);

    // Returns the string representation of |name|.
    const char* display_name() const;

    const StatsValueName name;
    // TODO(tommi): Support more value types than string.
    const std::string value;

   private:
    DISALLOW_COPY_AND_ASSIGN(Value);
  };

  typedef rtc::linked_ptr<Value> ValuePtr;
  typedef std::vector<ValuePtr> Values;

  // Ownership of |id| is passed to |this|.
  explicit StatsReport(rtc::scoped_ptr<Id> id);

  // Factory functions for various types of stats IDs.
  static rtc::scoped_ptr<Id> NewBandwidthEstimationId();
  static rtc::scoped_ptr<Id> NewTypedId(StatsType type, const std::string& id);
  static rtc::scoped_ptr<Id> NewIdWithDirection(
      StatsType type, const std::string& id, Direction direction);
  static rtc::scoped_ptr<Id> NewCandidateId(bool local, const std::string& id);
  static rtc::scoped_ptr<Id> NewComponentId(
      const std::string& content_name, int component);
  static rtc::scoped_ptr<Id> NewCandidatePairId(
      const std::string& content_name, int component, int index);

  const Id& id() const { return *id_.get(); }
  StatsType type() const { return id_->type(); }
  double timestamp() const { return timestamp_; }
  void set_timestamp(double t) { timestamp_ = t; }
  const Values& values() const { return values_; }

  const char* TypeToString() const;

  void AddValue(StatsValueName name, const std::string& value);
  void AddValue(StatsValueName name, int64 value);
  template <typename T>
  void AddValue(StatsValueName name, const std::vector<T>& value);
  void AddBoolean(StatsValueName name, bool value);

  void ReplaceValue(StatsValueName name, const std::string& value);

  void ResetValues();

  const Value* FindValue(StatsValueName name) const;

 private:
  // The unique identifier for this object.
  // This is used as a key for this report in ordered containers,
  // so it must never be changed.
  const rtc::scoped_ptr<Id> id_;
  double timestamp_;  // Time since 1970-01-01T00:00:00Z in milliseconds.
  Values values_;

  DISALLOW_COPY_AND_ASSIGN(StatsReport);
};

// Typedef for an array of const StatsReport pointers.
// Ownership of the pointers held by this implementation is assumed to lie
// elsewhere and lifetime guarantees are made by the implementation that uses
// this type.  In the StatsCollector, object ownership lies with the
// StatsCollection class.
typedef std::vector<const StatsReport*> StatsReports;

// A map from the report id to the report.
// This class wraps an STL container and provides a limited set of
// functionality in order to keep things simple.
// TODO(tommi): Use a thread checker here (currently not in libjingle).
class StatsCollection {
 public:
  StatsCollection();
  ~StatsCollection();

  // TODO(tommi): shared_ptr (or linked_ptr)?
  typedef std::list<StatsReport*> Container;
  typedef Container::iterator iterator;
  typedef Container::const_iterator const_iterator;

  const_iterator begin() const;
  const_iterator end() const;
  size_t size() const;

  // Creates a new report object with |id| that does not already
  // exist in the list of reports.
  StatsReport* InsertNew(rtc::scoped_ptr<StatsReport::Id> id);
  StatsReport* FindOrAddNew(rtc::scoped_ptr<StatsReport::Id> id);
  StatsReport* ReplaceOrAddNew(rtc::scoped_ptr<StatsReport::Id> id);

  // Looks for a report with the given |id|.  If one is not found, NULL
  // will be returned.
  StatsReport* Find(const StatsReport::Id& id);
  // TODO(tommi): we should only need one of these.
  StatsReport* Find(const rtc::scoped_ptr<StatsReport::Id>& id);

 private:
  Container list_;
};

}  // namespace webrtc

#endif  // TALK_APP_WEBRTC_STATSTYPES_H_
