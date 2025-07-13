import cv2
import face_recognition

video_capture = cv2.VideoCapture(0)

known_image = face_recognition.load_image_file("user.jpg")
known_encoding = face_recognition.face_encodings(known_image)[0]

while True:
    ret, frame = video_capture.read()
    rgb_frame = frame[:, :, ::-1]
    
    face_locations = face_recognition.face_locations(rgb_frame)
    face_encodings = face_recognition.face_encodings(rgb_frame, face_locations)

    for face_encoding in face_encodings:
        matches = face_recognition.compare_faces([known_encoding], face_encoding)
        if True in matches:
            print("Authorized user detected.")
            # You can call your servo motor unlock function here
        else:
            print("Unauthorized access attempt.")

    cv2.imshow('Video', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

video_capture.release()
cv2.destroyAllWindows()
