import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';

export default defineConfig({
  plugins: [react()],
  server: {
    open: true, // Optional: Opens the app in your browser when the server starts
  },
  resolve: {
    alias: {
      '@': '/src', // Optional: Use `@` as an alias for the `src` directory
    },
  },
});
