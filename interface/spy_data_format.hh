#ifndef _spy_data_format_hh
#define _spy_data_format_hh
namespace spydataformat
{
  enum class MuonInfo : char {ID = 0, REL_ISOLATION = 18};
  enum class ElectronInfo : char {ID = 0, REL_ISOLATION = 18};
  enum class TauInfo : char {ID = 0};
  enum class JetInfo : char {JETPGID = 1, BTAG = 33, GENJETPT = 34};
};
#endif
