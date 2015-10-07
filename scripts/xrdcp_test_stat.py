#!/usr/bin/env python
for ind in range(0, 101):
    with open ("xrdcp_test" + str(ind) + ".txt", "r") as myfile:
        data=myfile.read();
        for k in range(0, len(data.split())):
            word = data.split()[k]
            if (word == "host"):
                host = data.split()[k + 1]
                failed = False
                if data.find("0B/s") > -1:
                    failed = True
                print "%u\t%s\t\t\t%s" % (ind, host, failed)
                break
            if k == len(data.split()) -1:
                print ind, "\tNONE SHOWN" 
