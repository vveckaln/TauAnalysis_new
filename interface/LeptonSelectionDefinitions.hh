namespace ElecId
{
  enum ElecId  {Veto, Loose, Medium, Tight, LooseMVA, MediumMVA, TightMVA}; 
}
namespace ElecIso
{
  enum ElecIso {Veto, Loose, Medium, Tight};
}

namespace MuonId
{
  enum MuonId  {Loose, Soft, Tight, StdLoose, StdSoft, StdTight};
}
namespace MuonIso
{
  enum MuonIso {Loose,Tight}; 
}
const unsigned char run_number = 2;
const unsigned char region_number = 2;
const unsigned char Iso_types = 4; 

const float full5x5_sigmaIetaIeta_ref[run_number][region_number][Iso_types] = 
  {
    {
      {0.012,  0.0105, 0.0101, 0.0101},
      {0.0339, 0.0318, 0.0287, 0.0287}
    },
    {
      {0.0114, 0.0103, 0.0101, 0.0101},
      {0.0352, 0.0301, 0.0283, 0.0279}
    }
  };

const float abs_dEtaIn_ref[run_number][region_number][Iso_types] =
  {
    {
      {0.0126, 0.00976, 0.0094, 0.00864},
      {0.0109, 0.00952, 0.00773, 0.00762}
    },
    {
      {0.0152, 0.0105, 0.0103, 0.00926 },
      {0.0113, 0.00814, 0.00733, 0.00724}
    }
  };

const float abs_dPhiIn_ref[run_number][region_number][Iso_types] =
  {
    {
      {0.107, 0.0929, 0.0296, 0.0286},
      {0.219, 0.181, 0.148, 0.0439 }
    },
    {
      {0.216, 0.115, 0.0336, 0.0336 },
      {0.237, 0.182, 0.114, 0.0918}
    }
  };
	
const float hOverE_ref[run_number][region_number][Iso_types] =
  {
    {
      {0.186, 0.0765, 0.0372, 0.0342 },
      {0.0962, 0.0824, 0.0546, 0.0544}
    },
    {
      {0.181, 0.104, 0.0876, 0.0597  },
      {0.116, 0.0897, 0.0678, 0.0615 }
    }
  };

const float relIsoWithEA_ref[2][2][4] =
  {
    {
      {0.161, 0.118, 0.0987, 0.0591 },
      {0.193, 0.118, 0.0902, 0.0759  }
    },
    {
      {0.126, 0.0893, 0.0766, 0.0354  },
      {0.144, 0.121, 0.0678, 0.0646  }
    }
  };
  
const float ooEmooP_ref[run_number][region_number][Iso_types] =
  {
    {
      {0.239, 0.184, 0.118, 0.0116 },
      {0.141, 0.125, 0.104, 0.01  }
    },
    {
      {0.207, 0.102, 0.0174, 0.012  },
      {0.174, 0.126, 0.0898, 0.00999  }
    }
  };
  
static const float abs_d0_ref[run_number][region_number][Iso_types] =
  {
    {
      {0.0621, 0.0227, 0.0151, 0.0103 },
      {0.279, 0.242, 0.0535, 0.0377  }
    },
    {
      {0.279, 0.242, 0.0535, 0.0377  },
      {0.222, 0.118, 0.0739, 0.0351 }
    }
  };

const float abs_dz_ref[run_number][region_number][Iso_types] =
  {
    {
      {0.613, 0.379, 0.238, 0.170 },
      {0.947, 0.921, 0.572, 0.571 }
    },
    {
      {0.472, 0.41, 0.373, 0.0466  },
      {0.921, 0.822, 0.602, 0.417 }
    }
  };

const unsigned char expectedMissingInngerHit[run_number][region_number][Iso_types] =
  {
    {
      {2, 2, 2, 2  },
      {3, 1, 1, 1  }
    },
    {
      {2, 2, 2, 2  },
      {3, 1, 1, 1 }
    }
  };

static const unsigned char expectedMissingInngerHits[run_number][region_number][Iso_types] =
  {
    {
      {2, 2, 2, 2  },
      {3, 1, 1, 1  }
    },
    {
      {2, 2, 2, 2  },
      {3, 1, 1, 1 }
    }
  };

const bool pass_conv_veto_ref[run_number][region_number][Iso_types] = 
  {
    {
      {true, true, true, true},
      {true, true, true, true}
    },
    {
      {true, true, true, true},
      {true, true, true, true}
    }
  };
