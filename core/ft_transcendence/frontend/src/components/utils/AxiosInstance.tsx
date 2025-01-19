import axios from "axios";
const apiBaseUrl = import.meta.env.VITE_API_BASE_URL;


const axiosInstance = axios.create({
  baseURL: apiBaseUrl, // Backend URL
  withCredentials: true, // Ensures cookies are sent
});

axiosInstance.interceptors.response.use(
  (response) => {
    // Pass through successful responses
    return response;
  },
  (error) => {
    if (error.response?.status === 401) {
      // Excluded URLs (use exact paths or dynamic matching as needed)
      const excludedUrls = ["/users/auth/verify/", "/users/login/"];
      const requestUrl = new URL(error.config.url, error.config.baseURL)
        .pathname;

      // Check if the request URL matches an excluded URL
      if (excludedUrls.includes(requestUrl)) {
        console.info("401 response for excluded URL:", requestUrl);
        return Promise.reject(error); // Let the calling code handle it
      }

      // Global 401 handling for other URLs
      console.warn("Unauthorized - redirecting to login");
      window.location.href = "/"; // Adjust the path to your login route
    }

    // Reject other errors for individual handling
    return Promise.reject(error);
  }
);

export default axiosInstance;
