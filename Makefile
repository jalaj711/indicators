IDIR=include
ODIR=bin
SDIR=src
CC=gcc
CFLAGS=-I$(IDIR) -O0 -Winline -Wall -Wextra

OUTFILE=indicators

LIBS=-lm 

OBJS = 	ema 			\
		sma 			\
		macd			\
		rsi			\
		stochastic	\
		williams_r	\
		mfi			\
		bollinger	\
		atr			\
		supertrend	\
		keltner		\
		cci			\
		linreg_slope \
		obv \
		utils/rw_minmax			\
		utils/deque		

all: indicators bench		

bench: indicators
	gcc benchmark.c -L$(ODIR) -l$(OUTFILE) -I$(IDIR) -lm -O0 -o $(ODIR)/bench

indicators: $(OBJS)
	ar ruv $(ODIR)/lib$(OUTFILE).a $(addprefix $(ODIR)/, $(addsuffix .o, $(OBJS)))
	ranlib $(ODIR)/lib$(OUTFILE).a

$(OBJS):
	$(CC) -c $(SDIR)/$@.c -o $(ODIR)/$@.o $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 