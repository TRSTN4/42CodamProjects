import React, { useState } from "react";
import axiosInstance from "../utils/AxiosInstance";
import { useNavigate } from "react-router-dom";
// import "../../css/ChangeAvatar.css";

interface ChangeAvatarProps {
  avatarUrl: string;
  userId: number;
  username: string;
  onClose: () => void;
}

const ChangeAvatar: React.FC<ChangeAvatarProps> = ({
  avatarUrl,
  userId,
  username,
  onClose,
}) => {
  const [selectedFile, setSelectedFile] = useState<File | null>(null);
  const [uploadError, setUploadError] = useState<string | null>(null);
  const [isLoading, setIsLoading] = useState(false);
  const navigate = useNavigate();

  const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    if (e.target.files && e.target.files.length > 0) {
      setSelectedFile(e.target.files[0]);
      setUploadError(null);
    }
  };

  const handleUpload = async () => {
    if (!selectedFile) {
      setUploadError("Please select a file first.");
      return;
    }

    const formData = new FormData();
    formData.append("avatar", selectedFile);

    setIsLoading(true);

    try {
      const response = await axiosInstance.patch(
        `/users/${userId}/`,
        formData,
        {
          headers: {
            "Content-Type": "multipart/form-data",
          },
        }
      );

      if (response.status === 200) {
        navigate(`/users/${username}`);
      }
    } catch (error) {
      console.error("Error uploading avatar:", error);
      setUploadError("Failed to upload avatar. Please try again.");
    } finally {
      setIsLoading(false);
    }
  };

  const handleRemove = async () => {
	setIsLoading(true);
  
	try {
	  // Create a FormData object to handle the file upload
	  const formData = new FormData();
	  const filePath = "/images/default_avatar.jpg"; // Path in the public directory
	  const file = await fetch(filePath).then((res) => res.blob()); // Fetch the file as a Blob
  
	  formData.append("avatar", file, "default_avatar.jpg"); // Append the file with a name
  
	  // Send the PATCH request
	  const response = await axiosInstance.patch(
		`/users/${userId}/`,
		formData,
		{
		  headers: {
			"Content-Type": "multipart/form-data",
		  },
		}
	  );
  
	  if (response.status === 200) {
		navigate(`/users/${username}`);
	  }
	} catch (error) {
	  console.error("Error removing avatar:", error);
	  setUploadError("Failed to remove avatar. Please try again.");
	} finally {
	  setIsLoading(false);
	}
  };

  return (
    <div className="change-avatar-modal">
      <div className="modal-content">
        <h2 className="profile-title">Change Avatar</h2>
        <div className="current-avatar mt-2">
          <img
            src={avatarUrl}
            alt="Current Avatar"
            className="rounded-circle"
            style={{ width: "100px", height: "100px", objectFit: "cover" }}
          />
        </div>
        <div className="form-group mt-5">
          <label htmlFor="avatarUpload">Upload New Avatar</label>
          <input
            type="file"
            id="avatarUpload"
            className="form-control"
            onChange={handleFileChange}
          />
        </div>
        {uploadError && <p className="text-danger mt-2">{uploadError}</p>}
        <div className="modal-actions d-flex justify-content-between mt-5">
          <button
            className="btn btn-secondary"
            onClick={onClose}
            disabled={isLoading}
          >
            Cancel
          </button>
          <div>
            <button
              className="btn btn-danger me-2"
              onClick={handleRemove}
              disabled={isLoading}
            >
              Remove Avatar
            </button>
            <button
              className="btn btn-primary"
              onClick={handleUpload}
              disabled={isLoading || !selectedFile}
            >
              {isLoading ? "Uploading..." : "Upload"}
            </button>
          </div>
        </div>
      </div>
    </div>
  );
};

export default ChangeAvatar;
