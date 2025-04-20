IDIR=include
ODIR=bin
SDIR=src
CC=gcc
CFLAGS=-I$(IDIR) -O3 -Winline -Wall -Wextra

OUTFILE=indicators.a

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

bin: $(OBJS)
	ar ruv $(ODIR)/$(OUTFILE) $(addprefix $(ODIR)/, $(addsuffix .o, $(OBJS)))
	ranlib $(ODIR)/$(OUTFILE)

$(OBJS):
	$(CC) -c $(SDIR)/$@.c -o $(ODIR)/$@.o $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 