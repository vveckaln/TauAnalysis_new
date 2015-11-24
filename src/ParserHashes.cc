#include "CERN_RTU/TauAnalysis/interface/ParserHashes.hh"

namespace parserHashes
{
  const TString style_TString[] =
    {
      "kDot", "kPlus", "kStar", "kCircle", "kMultiply", "kFullDotSmall",
      "kFullDotMedium", "kFullDotLarge","kFullCircle", "kFullSquare", 
      "kFullTriangleUp", "kFullTriangleDown", "kOpenCircle", "kOpenSquare",
      "kOpenTriangleUp", "kOpenDiamond", "kOpenCross", "kFullStar",
      "kOpenStar", "kOpenTriangleDown","kFullDiamond", "kFullCross"
    };
  const Style_t style_hash[] = 
    {
      kDot, kPlus, kStar, kCircle, kMultiply, kFullDotSmall,
      kFullDotMedium, kFullDotLarge, kFullCircle, kFullSquare,
      kFullTriangleUp, kFullTriangleDown, kOpenCircle, kOpenSquare,
      kOpenTriangleUp, kOpenDiamond, kOpenCross, kFullStar,
      kOpenStar, kOpenTriangleDown, kFullDiamond, kFullCross
    };
  const unsigned long style_size = sizeof(style_hash)/sizeof(Style_t);
 
  const TString color_TString[] =
    {
      "kWhite", "kBlack", "kGray", "kRed", "kGreen", "kBlue", "kYellow",
      "kMagenta", "kCyan", "kOrange", "kSpring", "kTeal", "kAzure",
      "kViolet", "kPink"
    };
  const Color_t color_hash[] = 
    {
      kWhite, kBlack, kGray, kRed, kGreen, kBlue, kYellow, 
      kMagenta, kCyan, kOrange, kSpring, kTeal, kAzure, 
      kViolet, kPink
    };
  const unsigned long color_size = sizeof(color_hash)/sizeof(Color_t); 
}
