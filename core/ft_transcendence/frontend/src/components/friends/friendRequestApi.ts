import axiosInstance from '../utils/AxiosInstance';

export const sendFriendRequest = async (userId: number) => {
  return await axiosInstance.post(`/friends/send_friend_request/${userId}/`);
};

export const cancelFriendRequest = async (requestId: number) => {
  return await axiosInstance.delete(`/friends/cancel_friend_request/${requestId}/`);
};

export const acceptFriendRequest = async (requestId: number) => {
  return await axiosInstance.patch(`/friends/accept_friend_request/${requestId}/`);
};

export const declineFriendRequest = async (requestId: number) => {
  return await axiosInstance.delete(`/friends/decline_friend_request/${requestId}/`);
};

export const removeFriend = async (userId: number) => {
  return await axiosInstance.delete(`/friends/remove_friend/${userId}/`);
};

export const getFriendRequests = async () => {
  return await axiosInstance.get(`/friends/friend_requests/`);
};
