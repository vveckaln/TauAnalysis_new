include $(ROOTSYS)/etc/Makefile.arch
CLASS=rootdouble Table
DICTS=$(addsuffix Dict.$(SrcSuf), $(CLASS))

all: $(DICTS)


$(DICTS): 
	@echo "Generating dictionary $@..."
	$(ROOTCLING) -f $@ -c interface/$(subst Dict.$(SrcSuf),.h,$@) $(subst  Dict.$(SrcSuf),Linkdef.h,$@); \
	sed -in 's/"interface/"LIP\/TauAnalysis\/interface/g' $@;\
	mv $@ src;\
	mv $(subst .$(SrcSuf),_rdict.pcm,$@) $(CMSSW_BASE)/lib/slc6_amd64_gcc491/


clean:
	rm -f $(DICTS)

#$(DICTS): %.$(SrcSuf): interface/$(subst Dict.$(SrcSuf), .h, %) $(subst Dict.$(SrcSuf), LinkDef.h, %)
#	@echo "Generating dictionary $@..."
#	$(ROOTCLING) -f $@ -c $^
