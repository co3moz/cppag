#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <mmsystem.h>

#include "micromod.c"


#define SAMPLING_FREQ  48000  /* 48khz. */
#define OVERSAMPLE     2      /* 2x oversampling. */
#define NUM_CHANNELS   2      /* Stereo. */
#define BUFFER_SAMPLES 16386  /* 64k per buffer. */
#define NUM_BUFFERS    2      /* 4 buffers (256k). */

static HANDLE semaphore;
static WAVEHDR wave_headers[ NUM_BUFFERS ];
static short mix_buffer[ BUFFER_SAMPLES * NUM_CHANNELS * OVERSAMPLE ];
static short wave_buffers[ NUM_BUFFERS ][ BUFFER_SAMPLES * NUM_CHANNELS ];
static long filt_l, filt_r;

static void STDCALL wave_out_proc( HDRVR hdrvr, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2 ) {
        /*if( uMsg == WOM_OPEN ) printf( "Device open.\n" );*/
        if( uMsg == WOM_DONE ) ReleaseSemaphore( semaphore, 1, NULL );
        /*if( uMsg == WOM_CLOSE ) printf( "Device closed.\n" );*/
}

static void check_mmsys_error( int error ) {
        TCHAR string[ 64 ];
        if( error != MMSYSERR_NOERROR ) {
                waveOutGetErrorText( error, &string[ 0 ], 64 );
                fprintf( stderr, "%s", &string );
                exit( EXIT_FAILURE );
        }
}

static void load_module( char *file_name ) {
        FILE *file;
        void *module;
        long length, read, error;

        file = fopen( file_name, "rb" );
        if( file == NULL ) {
                fprintf( stderr, "Unable to open file.\n" );
                exit( EXIT_FAILURE );
        }

        module = malloc( 1084 );
        if( module == NULL ) {
                fprintf( stderr, "Unable to allocate memory.\n");
                exit( EXIT_FAILURE );
        }
        read = fread( module, 1, 1084, file );
        if( read != 1084 ) {
                fprintf( stderr, "Unable to read module header.\n");
                exit( EXIT_FAILURE );
        }
        length = micromod_calculate_mod_file_len( module );
        if( length < 0 ) {
                fprintf( stderr, "Module file type not recognised.\n");
                exit( EXIT_FAILURE );
        }
        free( module );

        module = malloc( length );
        if( module == NULL ) {
                fprintf( stderr, "Unable to allocate memory.\n");
                exit( EXIT_FAILURE );
        }
        error = fseek( file, 0, SEEK_SET );
        if( error != 0 ) {
                fprintf( stderr, "Unable to seek to start of file.\n");
                exit( EXIT_FAILURE );
        }
        read = fread( module, 1, length, file );
        if( read != length ) {
                fprintf( stderr, "Module file is truncated. %i bytes missing.\n", length - read );
        }
        error = fclose( file );
        if( error != 0 ) {
                fprintf( stderr, "Unable to close file.\n");
                exit( EXIT_FAILURE );
        }
        
        error = micromod_initialise( ( signed char * ) module, SAMPLING_FREQ * OVERSAMPLE );
        if( error != 0 ) {
                fprintf( stderr, "Unable to initialise replay.\n");
                exit( EXIT_FAILURE );
        }
}

static void print_module_info() {
        int inst;
        char string[ 23 ];
        for( inst = 0; inst < 16; inst++ ) {
                micromod_get_string( inst, string );
                printf( "%02i - %-22s ", inst, string );
                micromod_get_string( inst + 16, string );
                printf( "%02i - %-22s\n", inst + 16, string );
        }
}

static void downsample( short *input, short *output, long count ) {
        long in_idx, out_idx, out_l, out_r;
        in_idx = out_idx = 0;
        while( out_idx < count ) {      
                out_l = filt_l + ( input[ in_idx++ ] >> 1 );
                out_r = filt_r + ( input[ in_idx++ ] >> 1 );
                filt_l = input[ in_idx++ ] >> 2;
                filt_r = input[ in_idx++ ] >> 2;
                output[ out_idx++ ] = out_l + filt_l;
                output[ out_idx++ ] = out_r + filt_r;
        }
}
char* m; 
DWORD WINAPI ThreadFunc(void* data) {
	playmusic(m);
}

int playmusicthread() {
	HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
	if(thread)
		return 1;
	return 0;
}

int setmusiconthread(char* _m) {
	m = malloc(strlen(_m));
	strcpy(m, _m);
}

int playmusic( char* music ) {
        static WAVEFORMATEX wave_format;
        static HWAVEOUT h_wave_out;
        WAVEHDR *header;
        short *buffer;
        long idx, current_buffer, samples_remaining, count;

        /* Read module. */
        load_module( music );
        
        /* Calculate song length. */
        samples_remaining = micromod_calculate_song_duration();

        /* Initialise Wave Format Structure. */
        wave_format.wFormatTag = WAVE_FORMAT_PCM;
        wave_format.nChannels = NUM_CHANNELS;
        wave_format.nSamplesPerSec = SAMPLING_FREQ;
        wave_format.nAvgBytesPerSec = SAMPLING_FREQ * NUM_CHANNELS * 2;
        wave_format.nBlockAlign = NUM_CHANNELS * 2;
        wave_format.wBitsPerSample = 16;
        
        /* Initialise Waveform Buffers. */
        for( idx = 0; idx < NUM_BUFFERS; idx++ ) {
                header = &wave_headers[ idx ];
                memset( header, 0, sizeof( WAVEHDR ) );
                header->lpData = ( LPSTR ) &wave_buffers[ idx ][ 0 ];
                header->dwBufferLength = BUFFER_SAMPLES * NUM_CHANNELS * sizeof( short );
        }

        /* Initialise Semaphore. */
        semaphore = CreateSemaphore( NULL, NUM_BUFFERS, NUM_BUFFERS, "" );

        /* Open Audio Device. */
        check_mmsys_error( waveOutOpen( &h_wave_out, WAVE_MAPPER, &wave_format, ( DWORD ) wave_out_proc, 0, CALLBACK_FUNCTION ) );

        /* Play through once. */
        current_buffer = 0;
        while( samples_remaining > 0 ) {
                /* Wait for a buffer to become available. */
                WaitForSingleObject( semaphore, INFINITE );

                header = &wave_headers[ current_buffer ];
                buffer = &wave_buffers[ current_buffer ][ 0 ];
                
                /* Clear mix buffer and get audio from replay. */
                count = BUFFER_SAMPLES * OVERSAMPLE;
                if( count > samples_remaining ) count = samples_remaining;
                memset( mix_buffer, 0, BUFFER_SAMPLES * NUM_CHANNELS * OVERSAMPLE * sizeof( short ) );
                micromod_get_audio( mix_buffer, count );
                downsample( mix_buffer, buffer, BUFFER_SAMPLES * OVERSAMPLE );
                samples_remaining -= count;
                
                /* Submit buffer to audio system. */
                check_mmsys_error( waveOutUnprepareHeader( h_wave_out, header, sizeof( WAVEHDR ) ) );
                check_mmsys_error( waveOutPrepareHeader( h_wave_out, header, sizeof( WAVEHDR ) ) );
                check_mmsys_error( waveOutWrite( h_wave_out, header, sizeof( WAVEHDR ) ) );
                
                current_buffer++;
                if( current_buffer >= NUM_BUFFERS ) current_buffer = 0;
        }
		
        while( waveOutClose( h_wave_out ) == WAVERR_STILLPLAYING ) Sleep( 100 );
        return EXIT_SUCCESS;
}
