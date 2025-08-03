import os
import sys
import json
import subprocess
import time
import shutil
import io

# usage: python3 GRADE.py path-to-files submitted-file.cpp
TIMEOUT = 1

if len(sys.argv) != 3:
    print(f"usage:\n\tpython3 {sys.argv[0]} path-to-files submitted-file.cpp",file=sys.stderr)
    exit(1)


TASK = os.path.relpath(sys.argv[1])
GRADER = TASK+"/graders/grader.cpp"
CHECKER = TASK+"/checker/checker.cpp"
PROBLEM = TASK+"/problem.json"
SUBTASKS = TASK+"/subtasks/"
TESTS = TASK+"/tests"
TMP = ".tmp/"

AOUT = os.path.join(TMP,"a.out")
CHECKOUT = os.path.join(TMP,"check.out")

ANS = os.path.join(TMP,"ans.out")

exec_log = {}

def run_timer(*args,timeout=100,inp=subprocess.DEVNULL,outp=subprocess.DEVNULL) -> tuple[str|int,float]:
    args = (shutil.which(args[0]),*args[1:])
    program = subprocess.Popen(args,stdin=inp,stdout=outp,stderr=subprocess.DEVNULL)
    s=f"running {" ".join(args)}"
    if inp != subprocess.DEVNULL:
        s += f" <{inp.name}"
    s = s + ' '*(100-len(s))
    spin = "|/--\\"
    print(spin[int(time.time()*10)%len(spin)],s,end="\x1b[1G",file=sys.stderr,flush=True)
    start = time.time()
    rc = None
    while time.time() < start + timeout:
        try:
            rc = program.wait(0.1)
        except subprocess.TimeoutExpired:
            print(spin[int(time.time()*10)%len(spin)],end="\x1b[1D",file=sys.stderr,flush=True)
            continue
        break
    tot = time.time() - start
    print(end="\x1b[1G\x1b[2K",file=sys.stderr,flush=True)
    # print("\x1b[1D",time.time()-start,file=sys.stderr)
    if rc is None:
        program.kill()
        return ("TLE",tot)
    return (rc,tot)
        
                
            



def color(score: float) -> str:
    if score < 0: score = 0
    if score > 1: score = 1
    if score >= 0.5:
        return f"\x1b[38;2;{int(250-500*(score-0.5))};250;0m"
    else:
        return f"\x1b[38;2;250;{int(500*score)};0m"
def nocolor() -> str:
    return f"\x1b[0m"

# compile
os.makedirs(TMP,exist_ok=True)
if not os.path.exists(CHECKOUT):
    if CHECKER is not None and os.path.exists(CHECKER):
        r,t = run_timer("g++","--std=c++23","-O2",CHECKER,"-o",CHECKOUT)
        print(f"compiled checker in {t:.3f} seconds",file=sys.stderr)
        assert r == 0
    else:
        CHECKOUT = None

def check(FILE):
    global exec_log
    exec_log = {}
    print("\x1b[1m",f"checking {FILE}".ljust(30),"score    max time".rjust(55),"\x1b[0m",sep="")
    r,t=run_timer("g++","--std=c++23","-O2",FILE,GRADER,"-o",AOUT)
    print(f"compile{' '*70}{t:.6f}s",file=sys.stderr)
    assert r == 0
    s = 0
    for file in sorted(os.listdir(SUBTASKS)):
        r,t,m = test_subtask(os.path.join(SUBTASKS,file))
        if type(r) in [int,float]: s += r
        print(color(r/m if type(r) in [int,float] and m > 0 else m==0) +(f"testcase {file[:-len(".json")]}").ljust(30),f"{str(r).rjust(40)}/{str(m).ljust(3)}",color((1.0-t/TIMEOUT)**3),f"{t:.6f}s",nocolor())
    print(color(s/100),f"total".ljust(30),f"{str(s).rjust(41)}/100",nocolor(),sep="")

def test(testcase) -> tuple[float|str,float]: # returns evaluation and time
    global exec_log
    if testcase in exec_log:
        return exec_log[testcase]
    TIN = os.path.join(TESTS,testcase+".in")
    TOUT = os.path.join(TESTS,testcase+".out")
    with open(TIN,"+r") as tin:
        with open(ANS,"w") as ans:
            r,t = run_timer(f"./{AOUT}",inp=tin,outp=ans,timeout=TIMEOUT)
    if type(r) is str:
        exec_log[testcase] = (r,t)
        return (r,t)
    if r != 0:
        return (f"Return code nonzero: {r}",t)
    if CHECKOUT is not None:
        with open(os.path.join(TMP,"score.out"),"w+") as score:
            assert run_timer(f"./{CHECKOUT}",TIN,TOUT,ANS,outp=score)[0] == 0
            score.seek(0)
            eval = float(score.readline())
    else:
        with open(TOUT,"rb") as tout:
            with open(ANS,"rb") as ans:
                eval = int(tout.read() == ans.read())
    if eval == 0:
        exec_log[testcase] = ("WA",t)
        return ("WA",t)
    exec_log[testcase] = (eval,t)
    return (eval,t)

def test_subtask(subtask:str) -> tuple[float|str,float,int]:
    with open(subtask,"r") as f:
        data = json.load(f)
    mi = 1
    maxtime = 0.0
    for testcase in data['testcases']:
        r,t = test(testcase)
        maxtime = max(maxtime,t)
        if type(r) is str: return (r,maxtime,data['score'])
        mi = min(r,mi)
    return (mi * data['score'],maxtime,data['score'])

check(sys.argv[2])