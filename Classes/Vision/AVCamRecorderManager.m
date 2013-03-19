
# import "Core.h"
# import "AVCamRecorderManager.h"
# import "AVCamRecorder.h"

NNT_BEGIN_OBJC

@interface AVCamRecorderManager (RecorderDelegate) <AVCamRecorderDelegate>
@end

@interface AVCamRecorderManager ()

- (NSURL *) tempFileURL;
- (void) removeFile:(NSURL *)outputFileURL;
- (void) copyFileToDocuments:(NSURL *)fileURL;

@end

#pragma mark -
@interface AVCamCaptureManager (InternalUtilityMethods)
- (AVCaptureDevice *)cameraWithPosition:(AVCaptureDevicePosition)position;
- (AVCaptureDevice *)frontFacingCamera;
- (AVCaptureDevice *)backFacingCamera;
- (AVCaptureDevice *)audioDevice;
@end

@implementation AVCamRecorderManager

@synthesize recorder;

- (void)dealloc {
    [recorder release];    
    [super dealloc];
}

- (void)setupSession {
    [super setupSession];
    
     // Set up the movie file output
     NSURL *outputFileURL = [self tempFileURL];
     AVCamRecorder *newRecorder = [[AVCamRecorder alloc] initWithSession:[self session] outputFileURL:outputFileURL];
     [newRecorder setDelegate:self];
     
     // Send an error to the delegate if video recording is unavailable
     if (![newRecorder recordsVideo] && [newRecorder recordsAudio]) {
     NSString *localizedDescription = NSLocalizedString(@"Video recording unavailable", @"Video recording unavailable description");
     NSString *localizedFailureReason = NSLocalizedString(@"Movies recorded on this device will only contain audio. They will be accessible through iTunes file sharing.", @"Video recording unavailable failure reason");
     NSDictionary *errorDict = [NSDictionary dictionaryWithObjectsAndKeys:
     localizedDescription, NSLocalizedDescriptionKey, 
     localizedFailureReason, NSLocalizedFailureReasonErrorKey, 
     nil];
     NSError *noVideoError = [NSError errorWithDomain:@"AVCam" code:0 userInfo:errorDict];
     if ([[self delegate] respondsToSelector:@selector(captureManager:didFailWithError:)]) {
     [[self delegate] captureManager:self didFailWithError:noVideoError];
     }
     }
     
     [self setRecorder:newRecorder];
     [newRecorder release];
}

- (void)startRecording {
    if ([[UIDevice currentDevice] isMultitaskingSupported]) {
        // Setup background task. This is needed because the captureOutput:didFinishRecordingToOutputFileAtURL: callback is not received until AVCam returns
		// to the foreground unless you request background execution time. This also ensures that there will be time to write the file to the assets library
		// when AVCam is backgrounded. To conclude this background execution, -endBackgroundTask is called in -recorder:recordingDidFinishToOutputFileURL:error:
		// after the recorded file has been saved.
        [self setBackgroundRecordingID:[[UIApplication sharedApplication] beginBackgroundTaskWithExpirationHandler:^{}]];
    }
    
    [self removeFile:[[self recorder] outputFileURL]];
    [[self recorder] startRecordingWithOrientation:self.orientation];
}

- (void)stopRecording {
    [[self recorder] stopRecording];
}

- (NSURL *)tempFileURL {
    return [NSURL fileURLWithPath:[NSString stringWithFormat:@"%@%@", NSTemporaryDirectory(), @"output.mov"]];
}

- (void)removeFile:(NSURL *)fileURL {
    NSString *filePath = [fileURL path];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if ([fileManager fileExistsAtPath:filePath]) {
        NSError *error;
        if ([fileManager removeItemAtPath:filePath error:&error] == NO) {
            if ([[self delegate] respondsToSelector:@selector(captureManager:didFailWithError:)]) {
                [[self delegate] captureManager:self didFailWithError:error];
            }            
        }
    }
}

- (void)copyFileToDocuments:(NSURL *)fileURL {
	NSString *documentsDirectory = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
	NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
	[dateFormatter setDateFormat:@"yyyy-MM-dd_HH-mm-ss"];
	NSString *destinationPath = [documentsDirectory stringByAppendingFormat:@"/output_%@.mov", [dateFormatter stringFromDate:[NSDate date]]];
	[dateFormatter release];
	NSError	*error;
	if (![[NSFileManager defaultManager] copyItemAtURL:fileURL toURL:[NSURL fileURLWithPath:destinationPath] error:&error]) {
		if ([[self delegate] respondsToSelector:@selector(captureManager:didFailWithError:)]) {
			[[self delegate] captureManager:self didFailWithError:error];
		}
	}
}	

@end

#pragma mark -
@implementation AVCamRecorderManager (RecorderDelegate)

-(void)recorderRecordingDidBegin:(AVCamRecorder *)recorder {
    if ([[self delegate] respondsToSelector:@selector(captureManagerRecordingBegan:)]) {
        [[self delegate] captureManagerRecordingBegan:self];
    }
}

-(void)recorder:(AVCamRecorder *)recorder recordingDidFinishToOutputFileURL:(NSURL *)outputFileURL error:(NSError *)error {
	if ([[self recorder] recordsAudio] && ![[self recorder] recordsVideo]) {
		// If the file was created on a device that doesn't support video recording, it can't be saved to the assets 
		// library. Instead, save it in the app's Documents directory, whence it can be copied from the device via
		// iTunes file sharing.
		[self copyFileToDocuments:outputFileURL];
        
		if ([[UIDevice currentDevice] isMultitaskingSupported]) {
			[[UIApplication sharedApplication] endBackgroundTask:[self backgroundRecordingID]];
		}		
        
		if ([[self delegate] respondsToSelector:@selector(captureManagerRecordingFinished:)]) {
			[[self delegate] captureManagerRecordingFinished:self];
		}
	}
}

@end

NNT_END_OBJC