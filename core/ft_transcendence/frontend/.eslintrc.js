module.exports = {
    env: {
        browser: true,
        es2021: true,
    },
    extends: ['eslint:recommended', 'plugin:react/recommended'],
    plugins: ['unused-imports'],
    rules: {
        'unused-imports/no-unused-imports': 'error',
        'no-unused-vars': 'warn',
    },
};
